#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

/* exemple d'un client TCP simple */


int main(int argc, char *argv[])
{
    int sock_serv;
    int sock_len=sizeof(struct sockaddr_in);
    struct sockaddr_in listen_addr;

    /* Creation de la socket */
    if ((sock_serv=socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
    	perror("Creation de socket impossible");
    	return -1;
    }

    /* Preparation de l'adresse d'attachement:
       l'adresse sur laquelle nous allons nous connecter */
    listen_addr.sin_family=AF_INET;

    /* Adresse: localhost, on suppose que le serveur est sur la machine
       Attention: Conversion (interne) -> (reseau) avec htonl et htons
       On écoute sur le port 20000 */
    listen_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    listen_addr.sin_port=htons(20000);

    bind(sock_serv,(struct sockaddr*)&listen_addr,sock_len);
    listen(sock_serv, 1);
    int socket_service;
    socklen_t sock_serv_len=sizeof(struct sockaddr_in);
    socket_service = accept(sock_serv,(struct sockaddr*) &listen_addr, &sock_serv_len);

    char buf[20];
    char msg[20];
    strcpy(msg,"sent");


    printf("Connection OK, port %d\n", ntohs(listen_addr.sin_port));
    recv(socket_service,buf,20,0);
    printf("Message reçu: %s\n",buf);
    while(1)
    {
      send(socket_service, msg, 20, 0);
      recv(socket_service, buf, 20, 0);
      printf("Message reçu: %s\n",buf);
    }



    return 0;

}
