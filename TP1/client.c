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

  int socket_client;
  int socket_length = sizeof(struct sockaddr_in);
  struct sockaddr_in connect_addr;
  memset((char*) &connect_addr, 0, sizeof(connect_addr));

  if ((socket_client = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    perror("Creation de socket impossible");
    return -1;
  }
  else
  {
    printf("Descripteur socket_client: %d\n", socket_client);
  }

  connect_addr.sin_family = AF_INET;
  connect_addr.sin_port = htons(12345);
  inet_aton("127.0.0.1", &connect_addr.sin_addr);

  if ((connect(socket_client,(struct sockaddr*) &connect_addr, socket_length)) == -1) {
    perror ("Connexion échouée");
    exit(errno);
  }

  char buffer[100];
  char message[100];
  strcpy(message, "Client message");

  while(1)
  {
    read(socket_client, buffer, sizeof(buffer) - 1);
    printf("Received from Server: %s\n", buffer);
    write(socket_client, message, sizeof(message) - 1);
    printf("Sent to Server: %s\n", message);
  }
}
