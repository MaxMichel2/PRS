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
#define BUFFER_SIZE 1024
#define TIMEOUT_SECONDS 1
#define TIMEOUT_MICRO 0

int main(int argc, char* argv[])
{
	int port_sync, port_data;

	if (argc < 3)
	{
		printf("Too few arguments given.\n");
		printf("Format: ./server port_sync port_data\n");
		exit(1);
	}
	else if (argc > 3)
	{
		printf("Too many arguments given.\n");
		printf("Format: ./server port_sync port_data\n");
		exit(1);
	}
	else
	{
		port_sync = atoi(argv[1]);
		port_data = atoi(argv[2]);
	}

	// SYNCHRONIZATION SOCKET
	struct sockaddr_in server_addr;
	memset((char*)&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = DOMAIN;
	server_addr.sin_port = htons(port_sync);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	socklen_t socket_length = sizeof(server_addr);

	int socket_fd;
	if ((socket_fd = socket(DOMAIN, TYPE, PROTOCOL)) < 0)
	{
		perror("[-] Connection error");
		exit(1);
	}
	printf("[+] Synchronization socket created.\n");

	int reuse_sync = 1;
	setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse_sync, sizeof(reuse_sync));

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
	server_data_addr.sin_family = DOMAIN;
	server_data_addr.sin_port = htons(port_data);
	server_data_addr.sin_addr.s_addr = INADDR_ANY;
	socklen_t socket_data_length = sizeof(server_data_addr);

	int socket_data_fd;
	if ((socket_data_fd = socket(DOMAIN, TYPE, PROTOCOL)) < 0)
	{
		perror("[-] Connection error");
		exit(1);
	}
	printf("[+] Synchronization socket created.\n");

	int reuse_sync_data = 1;
	setsockopt(socket_data_fd, SOL_SOCKET, SO_REUSEADDR, &reuse_sync_data, sizeof(reuse_sync_data));

	// DATA SOCKET BIND
	if (bind(socket_data_fd, (struct sockaddr*) & server_data_addr, socket_data_length) < 0)
	{
		perror("[-] Bind error");
		exit(1);
	}
	printf("[+] Binded successfully to port %d.\n", port_data);

	// LISTEN
	listen(socket_fd, 1);
	listen(socket_data_fd, 1);

	// CLIENT SYNCHRONIZATION SOCKET
	struct sockaddr_in client_addr;
	memset((char*)&client_addr, 0, sizeof(client_addr));
	socklen_t client_length = sizeof(client_addr);
	char* client_IP;
	int client_port;

	// CLIENT DATA SOCKET
	struct sockaddr_in client_data_addr;
	memset((char*)&client_data_addr, 0, sizeof(client_data_addr));
	socklen_t client_data_length = sizeof(client_data_addr);
	char* client_data_IP;
	int client_data_port;

	// SELECT SETS
	fd_set socket_read_fd_set;
	FD_ZERO(&socket_read_fd_set);

	// TIMEOUT
	struct timeval timeout;
	timeout.tv_sec = TIMEOUT_SECONDS;
	timeout.tv_usec = TIMEOUT_MICRO;

	// CONNECTION
	int online = 1;
	int select_return, is_init;
	char buffer[BUFFER_SIZE];

	const char* underscore = "_";
	const char* dash = "-";
	const char* space = " ";

	while (online)
	{
		FD_SET(socket_fd, &socket_read_fd_set);
		FD_SET(socket_data_fd, &socket_read_fd_set);
		if ((select_return = select(10, &socket_read_fd_set, NULL, NULL, NULL)) < 0)
		{
			perror("[-] Select error\n");
			exit(1);
		}
		is_init = FD_ISSET(socket_fd, &socket_read_fd_set);
		if (is_init)
		{
			printf("Got here\n");
			recvfrom(socket_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*) & client_addr, &client_length);
			if (strcmp(buffer, "") != 0)
			{
				client_IP = inet_ntoa(client_addr.sin_addr);
				client_port= ntohs(client_addr.sin_port);
			}
			printf("Client: %s\n", buffer);
			if (strstr(buffer, "SYN") != NULL)
			{
				memset(buffer, 0, sizeof(buffer));
				sprintf(buffer, "SYN-ACK-%i", port_data);
				sendto(socket_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*) & client_addr, client_length);

				FD_CLR(socket_data_fd, &socket_read_fd_set);

				if ((select_return = select(10, &socket_read_fd_set, NULL, NULL, &timeout)) < 0)
				{
					perror("[-] Select error\n");
					exit(1);
				}

				if (select_return != 0)
				{
					recvfrom(socket_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*) & client_addr, &client_length);
					if (strstr(buffer, "ACK"))
					{
						memset(buffer, 0, sizeof(buffer));
					}
				}
			}
		}
		else
		{
			int recvfrom_return = recvfrom(socket_data_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*) & client_data_addr, &client_data_length);
			if (strcmp(buffer, "") != 0)
			{
				client_data_IP = inet_ntoa(client_data_addr.sin_addr);
				client_data_port = ntohs(client_data_addr.sin_port);
			}

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
				bzero(buffer, sizeof(buffer));
			}
		}
	}

	/*
	// SYNCHRONIZATION
	char syn[BUFFER_SIZE];
	char temp[25];
	recvfrom(socket_fd, syn, BUFFER_SIZE, 0, (struct sockaddr *) &client_addr, &socket_length);
	memset(syn, 0, BUFFER_SIZE);

	snprintf(temp, sizeof(temp), "SYN-ACK-%d", port_data);
	strcpy(syn, temp);
	sendto(socket_fd, syn, BUFFER_SIZE, 0, (struct sockaddr *) &client_addr, socket_length);
	memset(syn, 0, BUFFER_SIZE);

	recvfrom(socket_fd, syn, BUFFER_SIZE, 0, (struct sockaddr *) &client_addr, &socket_length);
	memset(syn, 0, BUFFER_SIZE);

	printf("[+] Synchronization successful\n");

	// DATA SOCKET
	close(socket_fd);
	
	if ((socket_data_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("[-] Connection error");
		exit(1);
	}
	printf("[+] Data socket created.\n");

    server_data_addr.sin_family = AF_INET;
	server_data_addr.sin_port = htons(port_data);
	server_data_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(socket_data_fd, (struct sockaddr*) &server_data_addr, sizeof(server_data_addr)) < 0)
	{
		perror("[-] Bind error");
		exit(1);
	}
	printf("[+] Bind data socket to port %d.\n", port_data);

	int reuse_data = 1;
	setsockopt(socket_data_fd, SOL_SOCKET, SO_REUSEADDR, &reuse_data, sizeof(reuse_data));

	int recvfrom_return;
	char buffer[1024];

    while (1)
    {

        recvfrom_return = recvfrom(socket_data_fd, buffer, sizeof(buffer), 0, (struct sockaddr *) &client_addr, &socket_length); 
        if (strcmp(buffer, ":exit") == 0)
        {
            printf("[-] Disconnected from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
			close(socket_data_fd);
            break;
        }
        else
        {
			printf("UDP Client: %s\n", buffer);
			sendto(socket_data_fd, buffer, recvfrom_return, 0, (struct sockaddr *) &client_addr, socket_length);
			memset(buffer, 0, sizeof(buffer));
            bzero(buffer, sizeof(buffer));
        }
    }
	close(socket_data_fd);
	*/
}