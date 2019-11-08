#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DOMAIN AF_INET
#define TYPE SOCK_DGRAM
#define PROTOCOL 0
#define BUFFER_SIZE 1025
#define TIMEOUT_SECONDS 1
#define TIMEOUT_MICRO 0

int get_data_port(char* buffer)
{
	char port[4];
	memcpy(&port, buffer+7, sizeof(port));
	int port_data = atoi(port);
	return port_data;
}

int main(int argc, char* argv[])
{
	// INITIALIZATION
	int port_sync, port_data;
	char addr[15];
	if (argc < 3)
	{
		printf("Too few arguments given.\n");
		printf("Format: ./client <adresseIP> <port>\n");
		exit(1);
	}
	else if (argc > 3)
	{
		printf("Too many arguments given.\n");
		printf("Format: ./client <adresseIP> <port>\n");
		exit(1);
	}
	else
	{
		strcpy(addr, argv[1]);
		port_sync = atoi(argv[2]);
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
			/*
			memset(buffer, 0, sizeof(buffer));
			sprintf(buffer, "BEGIN");
			sendto(socket_fd, buffer, strlen(buffer)+1, 0, (struct sockaddr*)& client_addr, sizeof(client_addr));
			*/
			/*
			memset(buffer, 0, sizeof(buffer));
			printf("UDP Client: ");
			fgets(buffer, BUFFER_SIZE, stdin);
			buffer[strcspn(buffer, "\n")] = 0;
			sendto(socket_fd, buffer, sizeof(buffer), 0, (struct sockaddr*)& client_addr, sizeof(client_addr));

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
			
		}
	}
	*/
	return 0;
}