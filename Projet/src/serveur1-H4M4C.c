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
#include <sys/select.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <errno.h>
#include <math.h>
#include <string.h>

// GLOBAL VARIABLES _________________________________________________________________________________________________________________________________________________________________________________________

#define DOMAIN AF_INET
#define TYPE SOCK_DGRAM
#define PROTOCOL 0
#define BUFFER_SIZE 1500
#define TIMEOUT_SECONDS 0
#define TIMEOUT_MICRO 5000
#define MIN_PORT 1000
#define MAX_PORT 9999

char large_buffer[5000000000];

// FUNCTIONS _________________________________________________________________________________________________________________________________________________________________________________________

char* pad_sequence_number(int val)
{
	char *sequence = malloc(6*sizeof(char));
	sprintf(sequence, "%06d", val); // ZERO-PADDING
	return sequence;
}

void arguments(int argc, char* argv[]) // à tester !
{
  if (argc != 2)
  {
    fprintf(stderr, "Format : %s <port>\n", argv[0]);
    exit(1);
  }
  return;
}

int test_error(int n, char* msg)
{
    if(n < 0)
    {
        perror(msg);
        return 0;
    }
    else
    {
        return 1;
    }
}

// MAIN _________________________________________________________________________________________________________________________________________________________________________________________

int main(int argc, char* argv[])
{
    // DECLARATIONS _________________________________________________________________________________________________________________________________________________________________________________________

    // VARIABLES

    int public_socket;
    int private_socket;
    int public_port;
    int private_port;
    int stop = 1;

    // RECEIVED MESSAGE SIZES

    int syn_size, syn_ack_size, ack_size, req_size, message_size, multi_ack_size, end_size;

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

    public_socket = socket(DOMAIN, TYPE, PROTOCOL);
    test_error(public_socket, "[-] Public socket opening error\n");

    // PUBLIC STRUCTURE SETUP

    memset((char *) &public, 0, sizeof(public));
    public.sin_family = DOMAIN;
    public.sin_addr.s_addr = htonl(INADDR_ANY);
    public.sin_port = htons(public_port);

    // PRIVATE STRUCTURE SETUP

    memset((char *) &private, 0, sizeof(private));
    private.sin_family = DOMAIN;
    private.sin_addr.s_addr = htonl(INADDR_ANY);
    private.sin_port = htons(public_port); // private_port unassigned

    // STRUCTURE SIZES

    int public_size = sizeof(public);
    int private_size = sizeof(private);

    // BINDING

    bind(public_socket, (struct sockaddr *) &public, public_size);

    // MAIN INFINITE LOOP _________________________________________________________________________________________________________________________________________________________________________________________

    int main_loop = 1;
    int multi;

    while(main_loop)
    {
        // CLIENT CONNECTION _________________________________________________________________________________________________________________________________________________________________________________________

        memset(syn, 0, BUFFER_SIZE);
        syn_size = recvfrom(public_socket, syn, BUFFER_SIZE, 0, (struct sockaddr *) &public, &public_size);
        
        if((test_error(syn_size, "[-] \"SYN\" reception error\n")) && (memcmp(syn, "SYN", 3) == 0))
        {
            printf("got SYN\n");
            // PRIVATE SOCKET

            private_socket = socket(DOMAIN, TYPE, PROTOCOL);
            test_error(private_socket, "[-] Private socket opening error\n");

            // PRIVATE PORT SELECTION

            memset((char *) &private, 0, sizeof(private));
            private.sin_family = DOMAIN;
            private.sin_addr.s_addr = htonl(INADDR_ANY);
            private.sin_port = htons(MIN_PORT);

            int current_port = MIN_PORT;

            while((bind(private_socket, (struct sockaddr *) &private, sizeof(private)) < 0) && (current_port <= MAX_PORT))
            {
                current_port++;
                private.sin_port = htons(current_port);
            }
            printf("Detected port for client: %d\n", current_port);

            // SYN-ACK TRANSMISSION

            char syn_ack[BUFFER_SIZE];
            memset(syn_ack, 0, sizeof(syn_ack));
            sprintf(syn_ack, "SYN-ACK%d", current_port);
            syn_ack_size = sendto(public_socket, syn_ack, BUFFER_SIZE, 0, (struct sockaddr *) &public, public_size);
            test_error(syn_ack_size, "[-] \"SYN-ACK\" transmission error\n");

            // ACK RECEPTION

            memset(ack, 0, sizeof(ack));
            ack_size = recvfrom(public_socket, syn_ack, BUFFER_SIZE, 0, (struct sockaddr *) &public, public_size);
            test_error(ack_size, "[-] \"ACK\" reception error\n");

            if(memcmp(ack, "ACK", 3) != 0)
            {
                perror("[-] \"ACK\" reception error\n");
                return 0;
            }

            printf("Connection established: SYN = %s, SYN-ACK = %s, ACK = %s\n", syn, syn_ack, ack);

        }
        else
        {
            printf("fuck\n");
        }
    }
}