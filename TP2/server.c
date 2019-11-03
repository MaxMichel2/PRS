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

int main(int argc, char* argv[])
{
	int port, select_port;

	if (argc < 3)
	{
		printf("Too few arguments given.\n");
		printf("Format: ./server port select_port\n");
		exit(1);
	}
	else if (argc > 3)
	{
		printf("Too many arguments given.\n");
		printf("Format: ./server port select_port\n");
		exit(1);
	}
	else
	{
		port = atoi(argv[1]);
		select_port = atoi(argv[2]);
	}

	fd_set initial_fds;
	FD_ZERO(&initial_fds);

	pid_t child_pid;
	int socket_server, bind_ret, select_socket;
	int socket_length = sizeof(struct sockaddr_in);
	struct sockaddr_in listen_addr;
	memset((char*)&listen_addr, 0, sizeof(listen_addr));

	if ((socket_server = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("[-] Connection error");
		exit(1);
	}
	printf("[+] Socket created.\n");

	if ((select_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("[-] Select socket connection error");
		exit(1);
	}
	printf("[+] Select socket created.\n");

	listen_addr.sin_family = AF_INET;
	listen_addr.sin_port = htons(port);
	listen_addr.sin_addr.s_addr = INADDR_ANY;

	if ((bind_ret = bind(socket_server, (struct sockaddr*) & listen_addr, socket_length)) < 0)
	{
		perror("[-] Bind error");
		exit(1);
	}
	printf("[+] Bind to port %d.\n", port);

	if (listen(socket_server, 1) == 0)
	{
		printf("Listening...\n");
	}
	else
	{
		perror("[-] Bind error");
		exit(1);
	}

	int new_socket;
	socklen_t socket_server_length = sizeof(struct sockaddr_in);

	struct sockaddr_in client_socket;

	char buffer[1024];

	while (1)
	{
		new_socket = accept(socket_server, (struct sockaddr*) &client_socket, &socket_server_length);
		if (new_socket < 0)
		{
			exit(1);
		}
		printf("[+] Connection accepted from %s:%d\n", inet_ntoa(client_socket.sin_addr), ntohs(client_socket.sin_port));

		if ((child_pid = fork()) == 0)
		{
			close(socket_server);
			while (1)
			{
				read(new_socket, buffer, sizeof(buffer) - 1);
				buffer[strcspn(buffer, "\r\n")] = 0;
				if (strcmp(buffer, ":exit") == 0)
				{
					printf("[-] Disconnected from %s:%d\n", inet_ntoa(client_socket.sin_addr), ntohs(client_socket.sin_port));
					break;
				}
				else
				{
					printf("Client: %s\n", buffer);
					write(new_socket, buffer, strlen(buffer));
					buffer[strcspn(buffer, "\r\n")] = 0;
					bzero(buffer, sizeof(buffer));
				}
			}
		}
		else
		{
			close(new_socket);
		}
	}

	return 0;
}
