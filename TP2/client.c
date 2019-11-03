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

int main(int argc, char* argv[])
{
	int port = 0;
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
		port = atoi(argv[2]);
	}

	int socket_client;
	int socket_length = sizeof(struct sockaddr_in);
	struct sockaddr_in connect_addr;
	memset((char*)&connect_addr, 0, sizeof(connect_addr));

	if ((socket_client = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("[-] Connection error");
		exit(1);
	}
	printf("[+] Client socket created\n");

	int reuse = 1;
	setsockopt(socket_client, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

	connect_addr.sin_family = AF_INET;
	connect_addr.sin_port = htons(port);
	inet_aton(addr, &connect_addr.sin_addr);

	if ((connect(socket_client, (struct sockaddr*) & connect_addr, socket_length)) < 0) 
	{
		perror("[-] Connection error");
		exit(1);
	}
	printf("[+] Connected to server\n");

	char buffer[1024];

	while (1)
	{
		printf("Client: \t");
		fgets(buffer, sizeof(buffer), stdin);
		buffer[strcspn(buffer, "\r\n")] = 0;
		write(socket_client, buffer, sizeof(buffer) - 1);

		if (strcmp(buffer, ":exit") == 0)
		{
			close(socket_client);
			printf("[-] Disconnected from server\n");
			exit(1);
		}

		if (read(socket_client, buffer, sizeof(buffer) - 1) < 0)
		{
			perror("[-] Data reception error");
		}
		else
		{
			buffer[strcspn(buffer, "\r\n")] = 0;
			printf("Server: \t%s\n", buffer);
		}
	}

	return 0;
}
