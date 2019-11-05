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
#define BUFFER_SIZE 1024
#define TIMEOUT_SECONDS 1
#define TIMEOUT_MICRO 0

int get_data_port(char* buffer)
{
	char delim[] = "-";
	char port[20];
	char* ptr = strtok(buffer, delim); // ptr = "SYN"
	ptr = strtok(NULL, delim);      // ptr = "ACK"
	ptr = strtok(NULL, delim);      // ptr = port_data
	strcpy(port, ptr);
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

	// SYNCHRONIZATION SOCKET
	struct sockaddr_in server_addr; // Server synchronization address structure
	memset((char*)&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = DOMAIN;
	server_addr.sin_port = htons(port_sync); // Server port converted to network value
	inet_aton(addr, &server_addr.sin_addr); // Conversion of IP Address to network value and associated to server_addr
	socklen_t socket_length = sizeof(server_addr); // Address size

	int socket_fd;

	if ((socket_fd = socket(DOMAIN, TYPE, PROTOCOL)) < 0)
	{
		perror("[-] Connection error\n");
		exit(1);
	}
	printf("[+] Client synchronization socket created\n");

	int reuse_sync = 1;
	setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse_sync, sizeof(reuse_sync));

	// BIND
	int bind_return;

	if ((bind_return = bind(socket_fd, (struct sockaddr*) &server_addr, socket_length)) < 0)
	{
		perror("[-] Bind error\n");
		exit(1);
	}
	printf("[+] Binded successfully to port %d\n", port_sync);

	// SELECT SETS
	fd_set socket_read_fd_set;
	FD_ZERO(&socket_read_fd_set);
	FD_SET(socket_fd, &socket_read_fd_set);

	// TIMEOUT
	struct timeval timeout;
	timeout.tv_sec = TIMEOUT_SECONDS;
	timeout.tv_usec = TIMEOUT_MICRO;

	// CONNECTION
	int online = 1;
	int select_return;
	char buffer[BUFFER_SIZE];

	const char* underscore = "_";
	const char* dash = "-";
	const char* space = " ";

	while (online)
	{
		memset(buffer, 0, sizeof(buffer));
		sprintf(buffer, "SYN");
		sendto(socket_fd, buffer, strlen(buffer), 0, (struct sockaddr*) & server_addr, socket_length);

		if ((select_return = select(10, &socket_read_fd_set, NULL, NULL, &timeout)) < 0)
		{
			perror("[-] Select error\n");
			exit(1);
		}

		if (select_return != 0)
		{
			recvfrom(socket_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*) & server_addr, &socket_length);
			printf("%s\n", buffer);
			if (strstr(buffer, "SYN-ACK") != NULL)
			{
				int data_port = get_data_port(buffer);
				printf("New port: %d\n", data_port);

				memset(buffer, 0, sizeof(buffer));
				sprintf(buffer, "ACK");
				sendto(socket_fd, buffer, strlen(buffer), 0, (struct sockaddr*) & server_addr, socket_length);

				if ((select_return = select(10, &socket_read_fd_set, NULL, NULL, &timeout)) < 0)
				{
					perror("[-] Select error\n");
					exit(1);
				}

				if (select_return != 0)
				{
					server_addr.sin_port = htons(data_port);
					while (online)
					{
						printf("UDP Client: ");
						fgets(buffer, BUFFER_SIZE, stdin);
						buffer[strcspn(buffer, "\n")] = 0;
						sendto(socket_fd, buffer, sizeof(buffer), 0, (struct sockaddr*)& server_addr, socket_length);

						if (strcmp(buffer, ":exit") == 0)
						{
							close(socket_fd);
							printf("[-] Disconnected from server\n");
							exit(1);
						}
						int recvfrom_return;
						if ((recvfrom_return = recvfrom(socket_fd, buffer, sizeof(buffer), 0, (struct sockaddr*) & server_addr, &socket_length)) < 0)
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
			}

		}
	}

	/*
	// SYNCHRONIZATION
	char syn[BUFFER_SIZE];
	strcpy(syn, "SYN");
	sendto(socket_fd, syn, strlen(syn), 0, (struct sockaddr *) &server_addr, sizeof(server_addr));
	memset(syn, 0, BUFFER_SIZE);

	recvfrom(socket_fd, syn, BUFFER_SIZE, 0, (struct sockaddr *) &server_addr, &socket_length);
	char delim[] = "-";
	char port[20];
	char *ptr = strtok(syn, delim); // ptr = "SYN"
	ptr = strtok(NULL, delim);      // ptr = "ACK"
	ptr = strtok(NULL, delim);      // ptr = port_data
	strcpy(port, ptr);
	port_data = atoi(port);
	memset(syn, 0, BUFFER_SIZE);

	strcpy(syn, "ACK");
	sendto(socket_fd, syn, strlen(syn), 0, (struct sockaddr *) &server_addr, sizeof(server_addr));
	memset(syn, 0, BUFFER_SIZE);

	printf("[+] Synchronization successful\n");

	// DATA SOCKET
	close(socket_fd);

	if ((socket_data_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("[-] Connection error");
		exit(1);
	}
	printf("[+] Client data socket created\n");

	int reuse_data = 1;
	setsockopt(socket_data_fd, SOL_SOCKET, SO_REUSEADDR, &reuse_data, sizeof(reuse_data));

	server_data_addr.sin_family = AF_INET;
	server_data_addr.sin_port = htons(port_data);
	inet_aton(addr, &server_data_addr.sin_addr);

	int recvfrom_return;

	while (1)
	{
		printf("UDP Client: ");
		fgets(buffer, BUFFER_SIZE, stdin);
		buffer[strcspn(buffer, "\n")] = 0;
		sendto(socket_data_fd, buffer, sizeof(buffer), 0, (struct sockaddr *) &server_addr, sizeof(server_addr));

		if (strcmp(buffer, ":exit") == 0)
		{
			close(socket_data_fd);
			printf("[-] Disconnected from server\n");
			exit(1);
		}

		if ((recvfrom_return = recvfrom(socket_data_fd, buffer, sizeof(buffer), 0, (struct sockaddr *) &client_addr, &socket_length)) < 0)
		{
			perror("[-] Data reception error");
		}
		else
		{
			buffer[recvfrom_return] = 0;
			printf("Server: %s\n", buffer);
		}
	}
	*/
	return 0;
}