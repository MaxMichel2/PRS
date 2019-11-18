//Librairies_________________________________________________________________________________________________________________________________________________________________________________________

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



//Variables globales_________________________________________________________________________________________________________________________________________________________________________________

#define BUFSIZE 1500
#define PORTMIN 1000
#define PORTMAX 9999

char grandBuffer[5000000000];



//Fonctions__________________________________________________________________________________________________________________________________________________________________________________________

char* SequenceTrame(int n)
{
  char* seq;
  seq = (char*) malloc(6*sizeof(char));
  strcpy(seq,"000000");
  if(n<10)
  {
    sprintf(&seq[5], "%d", n);
    return seq;
  }
  else if(n<100)
  {
    sprintf(&seq[4], "%d", n);
    return seq;
  }
  else if(n<1000)
  {
    sprintf(&seq[3], "%d", n);
    return seq;
  }
  else if(n<10000)
  {
    sprintf(&seq[2], "%d", n);
    return seq;
  }
  else if(n<100000)
  {
    sprintf(&seq[1], "%d", n);
    return seq;
  }
  else if(n<1000000)
  {
    sprintf(&seq[0], "%d", n);
    return seq;
  }
  else
  {
    perror("Numéro de séquence invalide\n");
  }
}

void arguments(int argc, char** argv) // à tester !
{
  if (argc != 2)
  {
    fprintf(stderr, "Utilisation : %s <port>\n", argv[0]);
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



/*Main_____________________________________________________________________________________________________________________________________________________________________________________________
___________________________________________________________________________________________________________________________________________________________________________________________________
________________________________________*******************************************************************************************************____________________________________________________
________________________________________*******************************************************************************************************____________________________________________________
________________________________________*******************************************************************************************************____________________________________________________
_________________________________________________________________________________________________________________________________________________________________________________________________*/


int main(int argc, char **argv)
{

  //Déclarations_____________________________________________________________________________________________________________________________________________________________________________________

  //Déclarations variables
  int sockpublic;
  int sockprivate;
  int portpublic;
  int portprivate;
  int stop = 1;

  //Taille des messages reçus
  int ack, syn, synack, rqst, msg, multipleack, fin;

  //Déclarations structures
  struct sockaddr_in public;
  struct sockaddr_in private;

  //Déclarations messages ACK, SYNACK, SYN, RQST, MULTIPLEACK
  char MSG[BUFSIZE];
  char RQST[BUFSIZE];
  char SYN[BUFSIZE];
  char ACK[BUFSIZE];
  char MULTIPLEACK[9];




  //Initialisations______________________________________________________________________________________________________________________________________________________________________________________

  //Vérification du nombre d'arguments et récupération du port public
  arguments(argc, argv);
  portpublic = atoi(argv[1]);

  //Récupération de la socket publique
  sockpublic = socket(AF_INET, SOCK_DGRAM, 0);
  testerror(sockpublic, "Erreur d'ouverture de la socket publique\n");

  //Initialisation de la structure "public"
  bzero((char *) &public, sizeof(public));
  public.sin_family = AF_INET;
  public.sin_addr.s_addr = htonl(INADDR_ANY);
  public.sin_port = htons(portpublic); //Si bug, vérifier (unsigned short)

  //Initialisation de la structure "private"
  bzero((char *) &private, sizeof(private));
  private.sin_family = AF_INET;
  private.sin_addr.s_addr = htonl(INADDR_ANY);
  private.sin_port = htons(portpublic); //portprivate n'est pas encore défini, alors on met portpublic avant. Si bug, vérifier (unsigned short)

  //Taille des structures
  int publiclen = sizeof(public);
  int privatelen = sizeof(private);

  //Binding sur la socket publique et vérification
  bind(sockpublic, (struct sockaddr *) &public, publiclen);



  //Boucle infinie principale______________________________________________________________________________________________________________________________________________________________________________________

  int boucle_principale = 1;
  int multi;
  while (boucle_principale)
  {
    //Connexion avec le client______________________________________________________________________________________________________________________________________________________________________________________

    bzero(SYN, BUFSIZE);
    int syn = recvfrom(sockpublic, SYN, BUFSIZE, 0, (struct sockaddr*) &public, &publiclen);
    if( (testerror(syn, "Erreur de réception du SYN\n")) && (SYN[0] = 'S') && (SYN[1] = 'Y') && (SYN[2] = 'N') )
    {

      //Socket privée
      sockprivate = socket(AF_INET, SOCK_DGRAM, 0);
      testerror(sockprivate, "Erreur d'ouverture de la socket privée\n");

      //Choix du port privé
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

      //SYN-ACK : Copie du port et envoi du SYN-ACK
      char portchar[BUFSIZE];
      char SYNACK[]="SYN-ACK";
      sprintf(portchar, "%d", port);
      strcat(SYNACK, portchar);
      synack = sendto(sockpublic, SYNACK, BUFSIZE, 0, (struct sockaddr*) &public, publiclen); //flag bloquant ???
      testerror(synack, "Erreur d'envoi du SYN-ACK\n");

      //ACK : Réception
      bzero(ACK, BUFSIZE);
      ack = recvfrom(sockpublic, ACK, BUFSIZE, 0, (struct sockaddr*) &public, &publiclen);
      testerror(ack, "Erreur de réception du ACK (négatif)\n");
      if ( (ACK[0] != 'A') || (ACK[1] != 'C') || (ACK[2] != 'K') )
      {
        error("Erreur de réception du ACK (erroné)\n");
      }

      //Connexion établie
      printf("Connexion établie : SYN=%s, SYN-ACK=%s, ACK=%s\n", SYN, SYNACK, ACK);
      multi = fork();
      if (multi ==0)
      {



        //Demande et ouverture du fichier________________________________________________________________________________________________________________________________________________________________________

        //Réception du nom du fichier demandé
        bzero(RQST, BUFSIZE);
        rqst = recvfrom(sockprivate, RQST, BUFSIZE, 0, (struct sockaddr*) &private, &privatelen); //pk bufsize + 1 ??
        testerror(rqst, "Erreur de réception de la demande de fichier\n");
        //printf("Fichier demandé : %s\n", RQST);

        //Début du timer
        long int Tstart = clock();

        //Ouverture du fichier
        FILE * fichier;
        fichier = fopen(RQST,"rb");
        if(fichier==NULL)
        {
          printf("Impossible d'ouvrir le fichier demandé\n");
          exit(1);
        }

        //Taille du fichier
        fseek(fichier, 0L, SEEK_END);
        int sizeoffile = ftell(fichier);
        rewind(fichier); //Se replace au debut du fichier

        //Chargement du fichier dans le grandBuffer
        bzero(grandBuffer, sizeoffile);
        fread(&grandBuffer, 1, sizeoffile, fichier);
        fclose(fichier);

        char* NBSEQ;
        int last_ACK = 0;
        int last_seq = sizeoffile/(BUFSIZE-6) +1;
        int windowsize;
        windowsize = 1000;

        //Envoi du fichier par séquences____________________________________________________________________________________________________________________________________________________________

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
        }

        //Fin___________________________________________________________________________________________________________________________________________________________________________________________________________________

        //Fin du timer
        long int Tstop = clock();
        float temps = (float) (Tstop-Tstart)/CLOCKS_PER_SEC;
        printf("Débit en ko/s : %f\n",(float) sizeoffile/(1024*temps));

        //Envoi du message de fin et arrêt de la boucle principale
        memset(MSG,0,BUFSIZE);
        sprintf(MSG,"FIN");
        for (int i=0; i<=200000; i++)
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
