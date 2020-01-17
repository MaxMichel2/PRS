// LIBRARIES _________________________________________________________________________________________________________________________________________________________________________________________

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

// GLOBAL VARIABLES _________________________________________________________________________________________________________________________________________________________________________________________

#define BUFFER_SIZE 1500
#define MIN_PORT 1000
#define MAX_PORT 9999

char file_buffer[5000000000];

// FUNCTIONS _________________________________________________________________________________________________________________________________________________________________________________________

char* pad_sequence_number(int seq_nbr)
{
  char *sequence = malloc(6*sizeof(char));
	sprintf(sequence, "%06d", seq_nbr); // ZERO-PADDING
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

int test_error(int n, char* msg)
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
  int public_socket;
  int private_socket;
  int public_port;
  int private_port;
  int stop = 1;

  // RECEIVED MESSAGE SIZES

  int ack_size, syn_size, syn_ack_size, req_size, msg_size, multi_ack_size, end_size;

  // RTT VALUE

  float rtt;

  // STRUCTURES

  struct sockaddr_in public;
  struct sockaddr_in private;

  // MESSAGE BUFFERS

  char msg[BUFFER_SIZE];
  char req[BUFFER_SIZE];
  char syn[BUFFER_SIZE];
  char ack[BUFFER_SIZE];
  char multi_ack[9];

  // INITIALIZATION _________________________________________________________________________________________________________________________________________________________________________________________

  // ARGUMENT CHECK & PORT SETUP

  arguments(argc, argv);
  public_port = atoi(argv[1]);

  // PUBLIC SOCKET

  public_socket = socket(AF_INET, SOCK_DGRAM, 0);
  test_error(public_socket, "[-] Public socket opening error\n");

  // PUBLIC STRUCTURE SETUP

  bzero((char *) &public, sizeof(public));
  public.sin_family = AF_INET;
  public.sin_addr.s_addr = htonl(INADDR_ANY);
  public.sin_port = htons(public_port);

  // PRIVATE STRUCTURE SETUP

  bzero((char *) &private, sizeof(private));
  private.sin_family = AF_INET;
  private.sin_addr.s_addr = htonl(INADDR_ANY);
  private.sin_port = htons(public_port);

  // STRUCTURE SIZES

  int public_size = sizeof(public);
  int private_size = sizeof(private);

  // BINDING

  bind(public_socket, (struct sockaddr *) &public, public_size);

  // MAIN INFINITE LOOP _________________________________________________________________________________________________________________________________________________________________________________________

  int main_loop = 1;
  int multi;

  while (main_loop)
  {
    // CLIENT CONNECTION _________________________________________________________________________________________________________________________________________________________________________________________

    bzero(syn, BUFFER_SIZE);
    int syn_size = recvfrom(public_socket, syn, BUFFER_SIZE, 0, (struct sockaddr*) &public, &public_size);
    if((test_error(syn_size, "[-] \"SYN\" reception error\n")) && (syn[0] = 'S') && (syn[1] = 'Y') && (syn[2] = 'N') )
    {

      // PRIVATE SOCKET

      private_socket = socket(AF_INET, SOCK_DGRAM, 0);
      test_error(private_socket, "[-] Private socket opening error\n");

      // PRIVATE PORT SELECTION

      bzero((char *) &private, sizeof(private));
      private.sin_family = AF_INET;
      private.sin_addr.s_addr = htonl(INADDR_ANY);
      private.sin_port = htons(MIN_PORT);
      int current_port = MIN_PORT;

      while ((bind(private_socket, (struct sockaddr *) &private, sizeof(private)) < 0)&&(current_port <= MAX_PORT))
      {
        current_port++;
        private.sin_port = htons(current_port);
      }

      printf("Detected port for client: %d\n", current_port);

      // SYN-ACK TRANSMISSION

      char port_buffer[5];
      char syn_ack[]="SYN-ACK";
      sprintf(port_buffer, "%d", current_port);
      strcat(syn_ack, port_buffer);

      // RTT CALCULATION - TIMER START

      clock_t start_time = clock();

      syn_ack_size = sendto(public_socket, syn_ack, BUFFER_SIZE, 0, (struct sockaddr*) &public, public_size); //flag bloquant ???
      test_error(ack_size, "[-] recvfrom error\n");

      // ACK RECEPTION

      bzero(ack, BUFFER_SIZE);
      ack_size = recvfrom(public_socket, ack, BUFFER_SIZE, 0, (struct sockaddr*) &public, &public_size);
      test_error(ack_size, "Erreur de réception du ACK (négatif)\n");

      // RTT CALCULATION - TIMER END

      clock_t end_time = clock();

      rtt = (float) ((end_time - start_time)/CLOCKS_PER_SEC);

      printf("RTT time is: %f sec = %f usec\n", rtt, rtt * pow(10,9));

      if ((ack[0] != 'A') || (ack[1] != 'C') || (ack[2] != 'K') )
      {
        error("[-] \"ACK\" reception error\n");
      }

      // CONNECTION ESTABLISHED

      printf("Connection established: SYN = %s, SYN-ACK = %s, ACK = %s\n", syn, syn_ack, ack);
      multi = fork();

      if (multi == 0)
      {

        // REQUEST AND FILE OPENING _________________________________________________________________________________________________________________________________________________________________________________________

        //Réception du nom du fichier demandé
        bzero(req, BUFFER_SIZE);
        req_size = recvfrom(private_socket, req, BUFFER_SIZE, 0, (struct sockaddr*) &private, &private_size); //pk bufsize + 1 ??
        test_error(req_size, "[-] File request reception error\n");
        printf("File requested: %s\n", req);

        // FILE OPENING

        FILE * requested_file;
        requested_file = fopen(req,"rb");
        if(requested_file == NULL)
        {
          printf("[-] Unable to open requested file\n");
          exit(1);
        }

        // FILE SIZE

        fseek(requested_file, 0L, SEEK_END);
        int file_size = ftell(requested_file);
        rewind(requested_file);

        // LOAD FILE INTO LARGE BUFFER

        bzero(file_buffer, file_size);
        fread(&file_buffer, 1, file_size, requested_file);
        fclose(requested_file);

        char* sequence_number;
        int last_ack = 0;
        int previous_ack = 0;
        int final_sequence_number = file_size/(BUFFER_SIZE-6) +1;
        int window_size = 120;
        int ssthresh = 65535;

        // SET TIMEOUT ON SOCKET

        struct timeval socket_timeout;
        socket_timeout.tv_sec = 0;
    		socket_timeout.tv_usec = (int)(0.001 * rtt * pow(10,9));

        setsockopt(private_socket, SOL_SOCKET, SO_RCVTIMEO, &socket_timeout, sizeof(socket_timeout));
    		setsockopt(private_socket, SOL_SOCKET, SO_SNDTIMEO, &socket_timeout, sizeof(socket_timeout));

        // FILE TRANSMISSION _________________________________________________________________________________________________________________________________________________________________________________________

        while(last_ack!=final_sequence_number)
        {

          if (last_ack+window_size<final_sequence_number)
          {
            for(int i = last_ack+1; i<=last_ack+window_size; i++)
            {
              bzero(msg, BUFFER_SIZE);
              sequence_number=pad_sequence_number(i);
              memcpy(&msg[0], sequence_number, 6);
              memcpy(&msg[6], &file_buffer[(i-1)*(BUFFER_SIZE-6)], BUFFER_SIZE-6);
              msg_size = sendto(private_socket, msg, BUFFER_SIZE, 0, (struct sockaddr *) &private, private_size);
              multi_ack_size = recvfrom(private_socket, multi_ack, 9, MSG_DONTWAIT,(struct sockaddr *) &private, &private_size);
              last_ack = atoi(&multi_ack[3]);

            }
          }
          if (last_ack + window_size >= final_sequence_number)
          {
            for(int i = last_ack + 1; i < final_sequence_number; i++)
            {
              bzero(msg, BUFFER_SIZE);
              sequence_number=pad_sequence_number(i);
              memcpy(&msg[0], sequence_number, 6);
              memcpy(&msg[6], &file_buffer[(i-1)*(BUFFER_SIZE-6)], BUFFER_SIZE-6);
              msg_size = sendto(private_socket, msg, BUFFER_SIZE, 0, (struct sockaddr *) &private, private_size);
              multi_ack_size = recvfrom(private_socket, multi_ack, 9, MSG_DONTWAIT,(struct sockaddr *) &private, &private_size);
              last_ack = atoi(&multi_ack[3]);

            }
            bzero(msg, BUFFER_SIZE);
            sequence_number=pad_sequence_number(final_sequence_number);
            memcpy(&msg[0], sequence_number, 6);
            memcpy(&msg[6], &file_buffer[(final_sequence_number-1)*(BUFFER_SIZE-6)], file_size-(final_sequence_number-1)*(BUFFER_SIZE-6)+6);
            msg_size = sendto(private_socket, msg, file_size-(final_sequence_number-1)*(BUFFER_SIZE-6)+6, 0, (struct sockaddr *) &private, private_size);
          }

          multi_ack_size = recvfrom(private_socket, multi_ack, 9, MSG_DONTWAIT, (struct sockaddr *) &private, &private_size);
          last_ack = atoi(&multi_ack[3]);

        }

        printf("Window size: %d\n", window_size);
        // END _________________________________________________________________________________________________________________________________________________________________________________________

        memset(msg,0,BUFFER_SIZE);
        sprintf(msg,"FIN");

        for (int i=0; i<=100000; i++)
        {
          end_size = sendto(private_socket, msg, BUFFER_SIZE, 0, (struct sockaddr *) &private, private_size);
        }

        test_error(end_size, "[-] \"FIN\" transmission error\n");
        printf("End of file %s transfer\n", req);
        close(private_socket);
        bzero(syn_ack,BUFFER_SIZE);
        main_loop = 0;
      }
    }
  }
  close(public_socket);
}
