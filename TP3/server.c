#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DOMAIN AF_INET
#define TYPE SOCK_DGRAM
#define PROTOCOL 0
#define BUFFER_SIZE 1025
#define TIMEOUT_SECONDS 1
#define TIMEOUT_MICRO 0

int main(int argc, char* argv[])
{
	// INITIALIZATION
	int port_sync, port_data;
	char filename[BUFFER_SIZE];
	if (argc < 4)
	{
		printf("Too few arguments given.\n");
		printf("Format: ./server <port_sync> <port_data> <filename>\n");
		exit(1);
	}
	else if (argc > 4)
	{
		printf("Too many arguments given.\n");
		printf("Format: ./server <port_sync> <port_data> <filename>\n");
		exit(1);
	}
	else
	{
		port_sync = atoi(argv[1]);
		port_data = atoi(argv[2]);
		memcpy(filename, argv[3], sizeof(filename));
	}

	// SELECT RETURN
	int select_return;

	// SOCKET OPTION
	int opt = 1;

	// FILE DESCRIPTOR
	fd_set read_fd_set;

	// SYNCHRONIZATION SOCKET
	struct sockaddr_in server_addr;
	memset((char*)&server_addr, 0, sizeof(server_addr));

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

	server_addr.sin_family = DOMAIN;
	server_addr.sin_port = htons(port_sync);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	socklen_t socket_length = sizeof(server_addr);

	// SYNCHRONIZATION SOCKET BIND
	if (bind(socket_fd, (struct sockaddr*) &server_addr, socket_length) < 0)
	{
		perror("[-] Bind error");
		exit(1);
	}
	printf("[+] Binded successfully to port %d.\n", port_sync);

	// DATA SOCKET
	struct sockaddr_in server_data_addr;
	memset((char*)&server_data_addr, 0, sizeof(server_data_addr));

	int socket_data_fd;
	if ((socket_data_fd = socket(DOMAIN, TYPE, PROTOCOL)) < 0)
	{
		perror("[-] Connection error");
		exit(1);
	}
	printf("[+] Data socket created.\n");

	if(setsockopt(socket_data_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
	{
		perror("[-] setsockopt error");
		exit(1);
	}

	server_data_addr.sin_family = DOMAIN;
	server_data_addr.sin_port = htons(port_data);
	server_data_addr.sin_addr.s_addr = INADDR_ANY;

	socklen_t socket_data_length = sizeof(server_data_addr);

	// DATA SOCKET BIND
	if (bind(socket_data_fd, (struct sockaddr*) &server_data_addr, socket_data_length) < 0)
	{
		perror("[-] Bind error");
		exit(1);
	}
	printf("[+] Binded successfully to port %d.\n", port_data);

	// CLIENT SYNCHRONIZATION
	struct sockaddr_in client_addr;
	socklen_t client_length = sizeof(client_addr);

	// CLIENT DATA
	struct sockaddr_in client_data_addr;
	socklen_t client_data_length = sizeof(client_data_addr);
	char* client_data_IP;
	int client_data_port;

	// CONNECTION
	int online = 1;
	int sequence_number = 0;
	char sequence[7] = {0};
	sprintf(sequence, "%06d", sequence_number); // ZERO-PADDING
	int sync_done = 0;
	char buffer[BUFFER_SIZE];

	while(online)
	{
		FD_ZERO(&read_fd_set);
		if (!sync_done)
		{
			FD_SET(socket_fd, &read_fd_set);
		}
		FD_SET(socket_data_fd, &read_fd_set);

		if (((select_return = select(4, &read_fd_set, NULL, NULL, NULL))) < 0 && (errno!=EINTR))
		{
			perror("[-] Select error\n");
			exit(1);
		}

		if (FD_ISSET(socket_fd, &read_fd_set))
		{
			client_length = sizeof(client_addr);
			memset(buffer, 0, sizeof(buffer));
			recvfrom(socket_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*) &client_addr, &client_length);
			if (strstr(buffer, "SYN") != NULL)
			{
				memset(buffer, 0, sizeof(buffer));
				sprintf(buffer, "SYN-ACK%i", port_data);
				sendto(socket_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*) &client_addr, sizeof(client_addr));

				recvfrom(socket_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*) & client_addr, &client_length);
				if (strstr(buffer, "ACK"))
				{
					memset(buffer, 0, sizeof(buffer));
				}
			}

			printf("Finished synchronization\n");
			FD_CLR(socket_fd, &read_fd_set);
			sync_done = 1;
		}

		if (FD_ISSET(socket_data_fd, &read_fd_set))
		{
			/*
			memset(buffer, 0, sizeof(buffer));
			int recvfrom_return = recvfrom(socket_data_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*) & client_data_addr, &client_data_length);
			printf("%d\n", recvfrom_return);
			*/
			/*
			// QUESTION 3
			memset(buffer, 0, sizeof(buffer));
			int recvfrom_return = recvfrom(socket_data_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*) & client_data_addr, &client_data_length);
			if (recvfrom_return != 0)
			{
				client_data_IP = inet_ntoa(client_data_addr.sin_addr);
				client_data_port = ntohs(client_data_addr.sin_port);

				if (strcmp(buffer, ":exit") == 0)
				{
					printf("[-] Disconnected from %s:%d\n", client_data_IP, client_data_port);
					close(socket_data_fd);
					break;
				}
				else
				{
					printf("UDP Client: %s\n", buffer);
					sendto(socket_data_fd, buffer, recvfrom_return, 0, (struct sockaddr*) & client_data_addr, client_data_length);
					memset(buffer, 0, sizeof(buffer));
				}
			}
			*/
		}
	}

	return 0;
}