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

#define BUFFER_SIZE 1024

int main(int argc, char* argv[])
{
	int port_sync, port_data;
	char addr[15];
	if (argc < 3)
	{
		printf("Too few arguments given.\n");
		printf("Format: ./client adresseIP port\n");
		exit(1);
	}
	else if (argc > 3)
	{
		printf("Too many arguments given.\n");
		printf("Format: ./client adresseIP port\n");
		exit(1);
	}
	else
	{
		strcpy(addr, argv[1]);
		port_sync = atoi(argv[2]);
	}

	// SYNCHRONIZATION SOCKET

	int socket_sync_fd; 
	socklen_t socket_length;
	struct sockaddr_in server_sync_addr, client_addr;
	memset((char*)&server_sync_addr, 0, sizeof(server_sync_addr));

	if ((socket_sync_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("[-] Connection error");
		exit(1);
	}
	printf("[+] Client synchronization socket created\n");
	
	int reuse_sync = 1;
	setsockopt(socket_sync_fd, SOL_SOCKET, SO_REUSEADDR, &reuse_sync, sizeof(reuse_sync));

	server_sync_addr.sin_family = AF_INET;
	server_sync_addr.sin_port = htons(port_sync);
	inet_aton(addr, &server_sync_addr.sin_addr);

	// SYNCHRONIZATION
	
	char syn[BUFFER_SIZE];
	strcpy(syn, "SYN");
	sendto(socket_sync_fd, syn, strlen(syn), 0, (struct sockaddr *) &server_sync_addr, sizeof(server_sync_addr));
	memset(syn, 0, BUFFER_SIZE);

	recvfrom(socket_sync_fd, syn, BUFFER_SIZE, 0, (struct sockaddr *) &server_sync_addr, &socket_length);
	char delim[] = "-";
	char port[20];
	char *ptr = strtok(syn, delim); // ptr = "SYN"
	ptr = strtok(NULL, delim);      // ptr = "ACK"
	ptr = strtok(NULL, delim);      // ptr = port_data
	strcpy(port, ptr);
	port_data = atoi(port);
	printf("new port: %d\n", port_data);
	memset(syn, 0, BUFFER_SIZE);

	strcpy(syn, "ACK");
	sendto(socket_sync_fd, syn, strlen(syn), 0, (struct sockaddr *) &server_sync_addr, sizeof(server_sync_addr));
	memset(syn, 0, BUFFER_SIZE);

	printf("[+] Synchronization successful\n");

	server_sync_addr.sin_port = htons(port_data);
	
	int recvfrom_return;
	char buffer[BUFFER_SIZE];

	while (1)
	{
		printf("UDP Client: ");
		fgets(buffer, BUFFER_SIZE, stdin);
		buffer[strcspn(buffer, "\n")] = 0;
		sendto(socket_sync_fd, buffer, sizeof(buffer), 0, (struct sockaddr *) &server_sync_addr, sizeof(server_sync_addr));

		if (strcmp(buffer, ":exit") == 0)
		{
			close(socket_sync_fd);
			printf("[-] Disconnected from server\n");
			exit(1);
		}

		if ((recvfrom_return = recvfrom(socket_sync_fd, buffer, sizeof(buffer), 0, (struct sockaddr *) &client_addr, &socket_length)) < 0)
		{
			perror("[-] Data reception error");
		}
		else
		{
			buffer[recvfrom_return] = 0;
			printf("Server: %s\n", buffer);
		}
	}
	return 0;
}