#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define DOMAIN AF_INET
#define TYPE SOCK_DGRAM
#define PROTOCOL 0
#define BUFFER_SIZE 128
#define TIMEOUT_SECONDS 0
#define TIMEOUT_MICRO 5000

int get_data_port(char* buffer)
{
	char port[4];
	memcpy(&port, buffer+7, sizeof(port));
	int port_data = atoi(port);
	return port_data;
}

char *get_filename_ext(char *filename) {
    char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

void strip_ext(char *fname)
{
    char *end = fname + strlen(fname);

    while (end > fname && *end != '.' && *end != '\\' && *end != '/') {
        --end;
    }
    if ((end > fname && *end == '.') &&
        (*(end - 1) != '\\' && *(end - 1) != '/')) {
        *end = '\0';
    }  
}

int main(int argc, char* argv[])
{
	// INITIALIZATION
	int port_sync, port_data;
	char addr[15];
	char file_to_get[30];
	char file_to_send[30];
	char *extension;
	if (argc < 4)
	{
		printf("Too few arguments given.\n");
		printf("Format: ./client <adresseIP> <port> <file_to_get>\n");
		exit(1);
	}
	else if (argc > 4)
	{
		printf("Too many arguments given.\n");
		printf("Format: ./client <adresseIP> <port> <file_to_get>\n");
		exit(1);
	}
	else
	{
		memcpy(addr, argv[1], sizeof(addr));
		port_sync = atoi(argv[2]);
		memcpy(file_to_get, argv[3], sizeof(file_to_get));
		memcpy(file_to_send, argv[3], sizeof(file_to_send));
		extension = get_filename_ext(file_to_get);
		strip_ext(file_to_get);
	}

	// SOCKET OPTION
	int opt = 1;

	// SYNCHRONIZATION SOCKET
	struct sockaddr_in client_addr;
	memset((char*)&client_addr, 0, sizeof(client_addr));

	int socket_fd;
	if ((socket_fd = socket(DOMAIN, TYPE, PROTOCOL)) < 0)
	{
		perror("[-] Connection error");
		exit(1);
	}
	printf("[+] Synchronization socket created.\n");

	if(setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
	{
		perror("[-] setsockopt error");
		exit(1);
	}

	client_addr.sin_family = DOMAIN;
	client_addr.sin_port = htons(port_sync);
	client_addr.sin_addr.s_addr = INADDR_ANY;

	socklen_t socket_length = sizeof(client_addr);

	// FILE
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
    char unique[30];
    strftime(unique, sizeof(unique), "%d-%m-%y_%H-%M-%S.", t);
	char file_name[60];
	sprintf(file_name, "%s%s%s%s", file_to_get, "_received_", unique, extension);
	printf("%s\n", file_name);
	FILE* file_to_receive = fopen(file_name, "w");
  	if(file_to_receive == NULL)
	{
		perror("[-] File open error");
		exit(1);
	}

	// TIMEOUT
	struct timeval timeout;
	timeout.tv_sec = TIMEOUT_SECONDS;
	timeout.tv_usec = TIMEOUT_MICRO;

	// CONNECTION
	int online = 1;
	int sync_done = 0;
	char buffer[BUFFER_SIZE];

	while (online)
	{
		if (!sync_done)
		{
			memset(buffer, 0, sizeof(buffer));
			sprintf(buffer, "SYN");
			sendto(socket_fd, buffer, strlen(buffer), 0, (struct sockaddr*) & client_addr, sizeof(client_addr));
			recvfrom(socket_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*) & client_addr, &socket_length);
			if (strstr(buffer, "SYN-ACK") != NULL)
			{
				port_data = get_data_port(buffer);
				printf("New port: %d\n", port_data);

				memset(buffer, 0, sizeof(buffer));
				sprintf(buffer, "ACK");
				sendto(socket_fd, buffer, strlen(buffer), 0, (struct sockaddr*) & client_addr, sizeof(client_addr));
			}
			memset(buffer, 0, sizeof(buffer));
			printf("Finished synchronization\n");
			client_addr.sin_port = htons(port_data);
			sync_done = 1;
			socket_length = sizeof(client_addr);
		}
		else
		{	
			
			memset(buffer, 0, sizeof(buffer));
			strcpy(buffer, "BEGIN-");
			strcat(buffer, file_to_send);
			//sprintf(buffer, strcat("BEGIN-", file_to_get));
			sendto(socket_fd, buffer, strlen(buffer)+1, 0, (struct sockaddr*)& client_addr, sizeof(client_addr));
			
			/*
			memset(buffer, 0, sizeof(buffer));
			printf("UDP Client: ");
			fgets(buffer, BUFFER_SIZE, stdin);
			buffer[strcspn(buffer, "\n")] = 0;
			sendto(socket_fd, buffer, strlen(buffer)+1, 0, (struct sockaddr*)& client_addr, sizeof(client_addr));
			
			if (strcmp(buffer, ":exit") == 0)
			{
				close(socket_fd);
				printf("[-] Disconnected from server\n");
				exit(1);
			}
			int recvfrom_return;
			if ((recvfrom_return = recvfrom(socket_fd, buffer, sizeof(buffer), 0, (struct sockaddr*) & client_addr, &socket_length)) < 0)
			{
				perror("[-] Data reception error");
			}
			else
			{
				buffer[recvfrom_return] = 0;
				printf("Server: %s\n", buffer);
			}
			*/
		}
	}
	
	return 0;
}