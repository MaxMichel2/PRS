// LIBRARIES _________________________________________________________________________________________________________________________________________________________________________________________

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <pthread.h>

// GLOBAL VARIABLES _________________________________________________________________________________________________________________________________________________________________________________________

#define BUFSIZE 1500
#define PORTMIN 1000
#define PORTMAX 9999

char grandBuffer[5000000000];

//Fonctions__________________________________________________________________________________________________________________________________________________________________________________________

char* SequenceTrame(int n)
{
  char *sequence = malloc(6*sizeof(char));
	sprintf(sequence, "%06d", n); // ZERO-PADDING
	return sequence;
}

void arguments(int argc, char** argv)
{
  if (argc != 2)
  {
    fprintf(stderr, "Format : %s <port>\n", argv[0]);
    exit(1);
  }
  return;
}

void error(char *msg)
{
  perror(msg);
  exit(0);
}

int testerror(int n, char* msg) // à tester
{
  if (n < 0)
  {
    error(msg);
    return 0;
  }
  else
    return 1;
}

// MAIN _________________________________________________________________________________________________________________________________________________________________________________________

int main(int argc, char **argv)
{

  // DECLARATIONS _________________________________________________________________________________________________________________________________________________________________________________________

  // VARIABLES
  int sockpublic;
  int sockprivate;
  int portpublic;
  int portprivate;
  int stop = 1;

  // RECEIVED MESSAGE SIZES
  
  int ack, syn, synack, rqst, msg, multipleack, fin;

  // STRUCTURES
  
  struct sockaddr_in public;
  struct sockaddr_in private;

  // MESSAGE BUFFERS
  
  char MSG[BUFSIZE];
  char RQST[BUFSIZE];
  char SYN[BUFSIZE];
  char ACK[BUFSIZE];
  char MULTIPLEACK[9];

  // INITIALIZATION _________________________________________________________________________________________________________________________________________________________________________________________

  // ARGUMENT CHECK & PORT SETUP
  
  arguments(argc, argv);
  portpublic = atoi(argv[1]);

  // PUBLIC SOCKET
  
  sockpublic = socket(AF_INET, SOCK_DGRAM, 0);
  testerror(sockpublic, "Erreur d'ouverture de la socket publique\n");

  // PUBLIC STRUCTURE SETUP
  
  bzero((char *) &public, sizeof(public));
  public.sin_family = AF_INET;
  public.sin_addr.s_addr = htonl(INADDR_ANY);
  public.sin_port = htons(portpublic);

  // PRIVATE STRUCTURE SETUP
  
  bzero((char *) &private, sizeof(private));
  private.sin_family = AF_INET;
  private.sin_addr.s_addr = htonl(INADDR_ANY);
  private.sin_port = htons(portpublic);

  // STRUCTURE SIZES
  
  int publiclen = sizeof(public);
  int privatelen = sizeof(private);

  // BINDING
  
  bind(sockpublic, (struct sockaddr *) &public, publiclen);

  // MAIN INFINITE LOOP _________________________________________________________________________________________________________________________________________________________________________________________

  int boucle_principale = 1;
  int multi;
  while (boucle_principale)
  {
    // CLIENT CONNECTION _________________________________________________________________________________________________________________________________________________________________________________________

    bzero(SYN, BUFSIZE);
    int syn = recvfrom(sockpublic, SYN, BUFSIZE, 0, (struct sockaddr*) &public, &publiclen);
    if( (testerror(syn, "Erreur de réception du SYN\n")) && (SYN[0] = 'S') && (SYN[1] = 'Y') && (SYN[2] = 'N') )
    {

      // PRIVATE SOCKET
	  
      sockprivate = socket(AF_INET, SOCK_DGRAM, 0);
      testerror(sockprivate, "Erreur d'ouverture de la socket privée\n");

      // PRIVATE PORT SELECTION
	  
      bzero((char *) &private, sizeof(private));
      private.sin_family = AF_INET;
      private.sin_addr.s_addr = htonl(INADDR_ANY);
      private.sin_port = htons(PORTMIN);
      int port = PORTMIN;

      while ((bind(sockprivate, (struct sockaddr *) &private, sizeof(private)) < 0)&&(port <= PORTMAX))
      {
        port++;
        private.sin_port = htons(port);
      }
      printf("Le port retenu pour ce client est le n°%d\n", port);

      // SYN-ACK TRANSMISSION
	  
      char portchar[BUFSIZE];
      char SYNACK[]="SYN-ACK";
      sprintf(portchar, "%d", port);
      strcat(SYNACK, portchar);
      synack = sendto(sockpublic, SYNACK, BUFSIZE, 0, (struct sockaddr*) &public, publiclen); //flag bloquant ???
      testerror(synack, "Erreur d'envoi du SYN-ACK\n");

      // ACK RECEPTION
	  
      bzero(ACK, BUFSIZE);
      ack = recvfrom(sockpublic, ACK, BUFSIZE, 0, (struct sockaddr*) &public, &publiclen);
      testerror(ack, "Erreur de réception du ACK (négatif)\n");
      if ( (ACK[0] != 'A') || (ACK[1] != 'C') || (ACK[2] != 'K') )
      {
        error("Erreur de réception du ACK (erroné)\n");
      }

      // CONNECTION ESTABLISHED
      printf("Connexion établie : SYN=%s, SYN-ACK=%s, ACK=%s\n", SYN, SYNACK, ACK);
      multi = fork();
      if (multi ==0)
      {

        // REQUEST AND FILE OPENING _________________________________________________________________________________________________________________________________________________________________________________________

        //Réception du nom du fichier demandé
        bzero(RQST, BUFSIZE);
        rqst = recvfrom(sockprivate, RQST, BUFSIZE, 0, (struct sockaddr*) &private, &privatelen); //pk bufsize + 1 ??
        testerror(rqst, "Erreur de réception de la demande de fichier\n");
        //printf("Fichier demandé : %s\n", RQST);

        // FILE OPENING
		
        FILE * fichier;
        fichier = fopen(RQST,"rb");
        if(fichier==NULL)
        {
          printf("Impossible d'ouvrir le fichier demandé\n");
          exit(1);
        }

		// FILE SIZE
		
        fseek(fichier, 0L, SEEK_END);
        int sizeoffile = ftell(fichier);
        rewind(fichier);

        // LOAD FILE INTO LARGE BUFFER
		
        bzero(grandBuffer, sizeoffile);
        fread(&grandBuffer, 1, sizeoffile, fichier);
        fclose(fichier);

        char* NBSEQ;
        int last_ACK = 0;
        int last_seq = sizeoffile/(BUFSIZE-6) +1;
        int windowsize;
        windowsize = 120;

        // FILE TRANSMISSION _________________________________________________________________________________________________________________________________________________________________________________________

        while(last_ACK!=last_seq)
        {

          if (last_ACK+windowsize<last_seq)
          {
            for(int i = last_ACK+1; i<=last_ACK+windowsize; i++)
            {
              bzero(MSG, BUFSIZE);
              //bzero(MULTIPLEACK, 9);
              NBSEQ=SequenceTrame(i);
              memcpy(&MSG[0], NBSEQ, 6);
              memcpy(&MSG[6], &grandBuffer[(i-1)*(BUFSIZE-6)], BUFSIZE-6);
              msg = sendto(sockprivate, MSG, BUFSIZE, 0, (struct sockaddr *) &private, privatelen);
              multipleack = recvfrom(sockprivate, MULTIPLEACK, 9, MSG_DONTWAIT,(struct sockaddr *) &private, &privatelen);
            }
          }
          if ((last_ACK)+windowsize>=last_seq)
          {
            for(int i = last_ACK+1; i<last_seq; i++)
            {
              bzero(MSG, BUFSIZE);
              //bzero(MULTIPLEACK, 9);
              NBSEQ=SequenceTrame(i);
              memcpy(&MSG[0], NBSEQ, 6);
              memcpy(&MSG[6], &grandBuffer[(i-1)*(BUFSIZE-6)], BUFSIZE-6);
              msg = sendto(sockprivate, MSG, BUFSIZE, 0, (struct sockaddr *) &private, privatelen);
              multipleack = recvfrom(sockprivate, MULTIPLEACK, 9, MSG_DONTWAIT,(struct sockaddr *) &private, &privatelen);
            }
            bzero(MSG, BUFSIZE);
            NBSEQ=SequenceTrame(last_seq);
            memcpy(&MSG[0], NBSEQ, 6);
            memcpy(&MSG[6], &grandBuffer[(last_seq-1)*(BUFSIZE-6)], sizeoffile-(last_seq-1)*(BUFSIZE-6)+6);
            msg = sendto(sockprivate, MSG, sizeoffile-(last_seq-1)*(BUFSIZE-6)+6, 0, (struct sockaddr *) &private, privatelen);
            //multipleack = recvfrom(sockprivate, MULTIPLEACK, 9, MSG_DONTWAIT,(struct sockaddr *) &private, &privatelen);
          }
          multipleack = recvfrom(sockprivate, MULTIPLEACK, 9, MSG_DONTWAIT, (struct sockaddr *) &private, &privatelen);
          last_ACK = atoi(&MULTIPLEACK[3]);
          //printf("last_ack: %d\n", last_seq);
        }

        // END _________________________________________________________________________________________________________________________________________________________________________________________

        memset(MSG,0,BUFSIZE);
        sprintf(MSG,"FIN");
        for (int i=0; i<=100000; i++)
        {
          fin = sendto(sockprivate, MSG, BUFSIZE, 0, (struct sockaddr *) &private, privatelen);
        }
        testerror(fin, "Erreur d'envoi du message de fin.\n");
        printf("Fin de l'envoi du fichier %s\n", RQST);
        close(sockprivate);
        bzero(SYNACK,BUFSIZE);
        boucle_principale = 0;
      }
    }
  }
  close(sockpublic);
}
