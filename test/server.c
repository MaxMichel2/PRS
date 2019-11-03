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

#define BUFFER_SIZE 1024

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

	fd_set socket_fd_set;
	FD_ZERO(&socket_fd_set);

    int socket_sync_fd, socket_data_fd; 
	socklen_t socket_length;
	struct sockaddr_in server_sync_addr, server_data_addr, client_addr;
	memset((char*)&server_sync_addr, 0, sizeof(server_sync_addr));

	if ((socket_sync_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("[-] Connection error");
		exit(1);
	}
	printf("[+] Synchronization socket created.\n");

    server_sync_addr.sin_family = AF_INET;
	server_sync_addr.sin_port = htons(port_sync);
	server_sync_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(socket_sync_fd, (struct sockaddr*) &server_sync_addr, sizeof(server_sync_addr)) < 0)
	{
		perror("[-] Bind error");
		exit(1);
	}
	printf("[+] Bind synchronization socket to port %d.\n", port_sync);

	int reuse_sync = 1;
	setsockopt(socket_sync_fd, SOL_SOCKET, SO_REUSEADDR, &reuse_sync, sizeof(reuse_sync));
	
	int recvfrom_return;
	char buffer[1024];

    while (1)
    {
		FD_SET(socket_sync_fd, &socket_fd_set);
		FD_SET(socket_data_fd, &socket_fd_set);
		int select_return = select(10, &socket_fd_set, NULL, NULL, NULL);

		if(select_return < 0)
		{
			perror("[-] Select error");
			exit(1);
		}

		if(FD_ISSET(socket_sync_fd, &socket_fd_set))
		{
			// SYNCHRONIZATION

			char syn[BUFFER_SIZE];
			char temp[25];
			recvfrom(socket_sync_fd, syn, BUFFER_SIZE, 0, (struct sockaddr *) &client_addr, &socket_length);
			memset(syn, 0, BUFFER_SIZE);

			snprintf(temp, sizeof(temp), "SYN-ACK-%d", port_data);
			strcpy(syn, temp);
			sendto(socket_sync_fd, syn, BUFFER_SIZE, 0, (struct sockaddr *) &client_addr, socket_length);
			memset(syn, 0, BUFFER_SIZE);

			recvfrom(socket_sync_fd, syn, BUFFER_SIZE, 0, (struct sockaddr *) &client_addr, &socket_length);
			memset(syn, 0, BUFFER_SIZE);

			printf("[+] Synchronization successful\n");
		}

		if(FD_ISSET(socket_data_fd, &socket_fd_set)){

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
			printf("[+] Bind synchronization socket to port %d.\n", port_data);

			int reuse_data = 1;
			setsockopt(socket_data_fd, SOL_SOCKET, SO_REUSEADDR, &reuse_data, sizeof(reuse_data));

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
    }
	close(socket_sync_fd);
}