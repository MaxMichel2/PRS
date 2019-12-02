#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <math.h>

#define DOMAIN AF_INET
#define TYPE SOCK_DGRAM
#define PROTOCOL 0
#define BUFFER_SIZE 128
#define TIMEOUT_SECONDS 0
#define TIMEOUT_MICRO 5000

char* pad_sequence_number(int val)
{
	char *sequence = malloc(6*sizeof(char));
	sprintf(sequence, "%06d", val); // ZERO-PADDING
	return sequence;
}

int main(int argc, char* argv[])
{
	// INITIALIZATION
	int port_sync, port_data;
	//char filename[BUFFER_SIZE];
	if (argc < 3)
	{
		printf("Too few arguments given.\n");
		printf("Format: ./server <port_sync> <port_data>\n");
		exit(1);
	}
	else if (argc > 3)
	{
		printf("Too many arguments given.\n");
		printf("Format: ./server <port_sync> <port_data>\n");
		exit(1);
	}
	else
	{
		port_sync = atoi(argv[1]);
		port_data = atoi(argv[2]);
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

	// FILE
	FILE* file_to_transfer;
  	int ftt_fd;
  	char file_name[64];
  	int file_size;
	struct stat file_info;

	// WINDOW INTERVAL
	int window_start = 0;
	int window_end = 0;

	int window_size = 1;

	// TIMEOUT
	struct timeval timeout;
  	timeout.tv_sec = TIMEOUT_SECONDS;
	timeout.tv_usec = TIMEOUT_MICRO;

	// CONNECTION
	int online = 1;
	int sequence_number = 0;
	char *sequence = malloc(6*sizeof(char));
	sprintf(sequence, "%06d", sequence_number); // ZERO-PADDING
	int sync_done = 0;
	char send_buffer[BUFFER_SIZE];
	char recv_buffer[BUFFER_SIZE];
	char* block = malloc(BUFFER_SIZE-6);

	while(online)
	{
		FD_ZERO(&read_fd_set);
		if (!sync_done)
		{
			FD_SET(socket_fd, &read_fd_set);
		}
		FD_SET(socket_data_fd, &read_fd_set);

		if (((select_return = select(6, &read_fd_set, NULL, NULL, NULL))) < 0 && (errno!=EINTR))
		{
			perror("[-] Select error\n");
			exit(1);
		}

		if (FD_ISSET(socket_fd, &read_fd_set))
		{
			client_length = sizeof(client_addr);
			memset(send_buffer, 0, sizeof(send_buffer));
			recvfrom(socket_fd, send_buffer, BUFFER_SIZE, 0, (struct sockaddr*) &client_addr, &client_length);
			if (strstr(send_buffer, "SYN") != NULL)
			{
				memset(send_buffer, 0, sizeof(send_buffer));
				sprintf(send_buffer, "SYN-ACK%i", port_data);
				sendto(socket_fd, send_buffer, BUFFER_SIZE, 0, (struct sockaddr*) &client_addr, sizeof(client_addr));

				recvfrom(socket_fd, send_buffer, BUFFER_SIZE, 0, (struct sockaddr*) & client_addr, &client_length);
				if (strstr(send_buffer, "ACK"))
				{
					memset(send_buffer, 0, sizeof(send_buffer));
				}
			}

			printf("Finished synchronization\n");
			FD_CLR(socket_fd, &read_fd_set);
			sync_done = 1;
		}

		if (FD_ISSET(socket_data_fd, &read_fd_set))
		{
			
			memset(send_buffer, 0, sizeof(send_buffer));
			int recvfrom_return = recvfrom(socket_data_fd, send_buffer, BUFFER_SIZE, 0, (struct sockaddr*) & client_data_addr, &client_data_length);
			
			memcpy(&file_name, send_buffer+6, recvfrom_return-6);

			file_to_transfer = fopen(file_name, "rb");
			printf("File to transfer: %s\n", file_name);
			if (file_to_transfer == NULL)
			{
				perror("[-] File not found");
				exit(1);
			}

			ftt_fd = fileno(file_to_transfer);
			fstat(ftt_fd, &file_info);
			file_size = file_info.st_size;

			printf("File size: %d\n", file_size);
			char *file_buffer = malloc(file_size+3);
			if (file_buffer == 0)
			{
				perror("[-] Allocation error");
				exit(1);
			}
			fread(file_buffer, 1, file_size, file_to_transfer);
			fclose(file_to_transfer);

			int file_remainder = file_size%(BUFFER_SIZE-6);
			int total_segments = file_size/(BUFFER_SIZE-6);
			
			printf("Number of packets: %d\nRemainder: %d\n", total_segments, file_remainder);

			int i = 0;
			window_size = 1;
			while (window_start < file_size)
			{
				window_end = window_start + window_size;
				if (window_end > total_segments)
				{
					window_end = total_segments;
				}
				for (sequence_number = window_start; sequence_number <= window_end; sequence_number++)
				{
					i = (BUFFER_SIZE - 6) * sequence_number; // i will contain the starting byte
					sequence = pad_sequence_number(sequence_number);
					memcpy(send_buffer, sequence, 6);

					if (sequence_number == total_segments)
					{
						memcpy(send_buffer+6, file_to_transfer+i, file_remainder);
					}
					else
					{
						memcpy(send_buffer+6, file_to_transfer+i, BUFFER_SIZE-6);
					}

					if (sequence_number == total_segments)
					{
						sendto(socket_data_fd, send_buffer, file_remainder + 6, 0, (struct sockaddr*) & client_data_addr, client_data_length);
					}
					else
					{
						sendto(socket_data_fd, send_buffer, BUFFER_SIZE, 0, (struct sockaddr*) & client_data_addr, client_data_length);
					}
					printf("Last line of for loop");
				}
			}

			printf("End of loop\n");
			break;
			//printf("recvfrom_return: %d\tbuffer: %s\n", recvfrom_return, buffer);

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
					FD_CLR(socket_data_fd, &read_fd_set);
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