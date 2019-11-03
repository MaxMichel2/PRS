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

int main(int argc, char *argv[])
{

  int socket_server;
  int socket_length = sizeof(struct sockaddr_in);
  struct sockaddr_in listen_addr;
  memset((char*) &listen_addr, 0, sizeof(listen_addr));

  if ((socket_server = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    perror("Creation de socket impossible");
    return -1;
  }
  else
  {
    printf("Descripteur socket_serveur: %d\n", socket_server);
  }

  listen_addr.sin_family = AF_INET;
  listen_addr.sin_port = htons(12345);
  listen_addr.sin_addr.s_addr = INADDR_ANY;

  bind(socket_server, (struct sockaddr*) &listen_addr, socket_length);
  listen(socket_server, 1);

  int socket_service;
  socklen_t socket_server_length = sizeof(struct sockaddr_in);

  struct sockaddr_in client_socket;

  char buffer[100];
  char message[100];
  strcpy(message, "Server message");

  while(1)
  {
    socket_service = accept(socket_server, (struct sockaddr*) &client_socket, &socket_server_length);
    printf("Connexion établie, Descriptif socket: %d, Adresse IP: %s, Port: %d\n", socket_service, inet_ntoa(client_socket.sin_addr), ntohs(client_socket.sin_port));
    write(socket_service, message, sizeof(message) - 1);
    printf("Sent to Client: %s\n", message);
    read(socket_service, buffer, sizeof(buffer) -1);
    printf("Received from Client: %s\n", buffer);
  }
}
