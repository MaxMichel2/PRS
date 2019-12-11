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

int* ack_received = NULL;

// STRUCTURE FOR THREAD

struct ack_thread_args {
    char thread_multi_ack[10];
    int thread_multi_ack_size;
    int thread_private_socket;
    struct sockaddr_in thread_private;
    socklen_t thread_private_size;
    int thread_window_size;
    int thread_return_last_ack;
    char thread_msg[BUFFER_SIZE];
    char* thread_sequence_number;
    int thread_msg_size;
};

// FUNCTIONS _________________________________________________________________________________________________________________________________________________________________________________________

// PAD SEQUENCE

char* pad_sequence_number(int val)
{
	char *sequence = malloc(6*sizeof(char));
	sprintf(sequence, "%06d", val); // ZERO-PADDING
	return sequence;
}

// CHECK ARGUMENTS

void arguments(int argc, char* argv[]) // à tester !
{
  if (argc != 2)
  {
    fprintf(stderr, "Format : %s <port>\n", argv[0]);
    exit(1);
  }
  return;
}

// TEST ERRORS

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

// ACK RECEIVE

void *ack_receive(void* _args)
{
    struct ack_thread_args *args = (struct ack_thread_args *) _args; 
    int last_ack = 0;
    int previous_ack = 0;
    while(1)
    {
        memset(args->thread_multi_ack, 0, sizeof(args->thread_multi_ack));
        args->thread_multi_ack_size = recvfrom(args->thread_private_socket, args->thread_multi_ack, 10, MSG_WAITALL, (struct sockaddr *) &(args->thread_private), &(args->thread_private_size));
        args->thread_multi_ack[10]="\0";
        
        
        int i = 0;

        if(args->thread_multi_ack_size != -1)
        {
            previous_ack = last_ack;
            last_ack = atoi(&(args->thread_multi_ack[3]));
            if(ack_received[last_ack-1] == 0)
            {
                for(i = 0; i < last_ack-1; i++)
                {
                    ack_received[i] = 1;
                }
            }
            args->thread_return_last_ack = last_ack;
        }
        else
        {
            memset(args->thread_msg, 0, BUFFER_SIZE);
            args->thread_sequence_number = pad_sequence_number(last_ack);
            memcpy(&(args->thread_msg[0]), args->thread_sequence_number, 6);
            memcpy(&(args->thread_msg[6]), &large_buffer[(last_ack - 1) * (BUFFER_SIZE - 6)], BUFFER_SIZE - 6);
            args->thread_msg_size = sendto(args->thread_private_socket, args->thread_msg, BUFFER_SIZE, 0, (struct sockaddr *) &(args->thread_private), args->thread_private_size);
        }
    }
}

// INITIALIZE ACK ARRAY

void ack_array_setup(int size)
{
    if(!ack_received)
    {
        ack_received = (int *) calloc((size-1), sizeof(int));
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

    int syn_size, syn_ack_size, ack_size, req_size, msg_size, multi_ack_size, end_size;

    // STRUCTURES

    struct sockaddr_in public;
    struct sockaddr_in private;

    // MESSAGE BUFFERS

    char msg[BUFFER_SIZE];
    char req[BUFFER_SIZE];
    char syn[BUFFER_SIZE];
    char syn_ack[BUFFER_SIZE];
    char ack[BUFFER_SIZE];
    char multi_ack[10]="\0";

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

    socklen_t public_size = sizeof(public);
    socklen_t private_size = sizeof(private);

    // BINDING

    bind(public_socket, (struct sockaddr *) &public, public_size);

    // TIMEOUT

    struct timeval socket_timeout;
    socket_timeout.tv_sec = 0;
    socket_timeout.tv_usec = 500;

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
            // PRIVATE SOCKET

            private_socket = socket(DOMAIN, TYPE, PROTOCOL);
            test_error(private_socket, "[-] Private socket opening error\n");
            setsockopt(private_socket, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *) &socket_timeout, sizeof(struct timeval));

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

            memset(syn_ack, 0, sizeof(syn_ack));
            sprintf(syn_ack, "SYN-ACK%d", current_port);
            syn_ack_size = sendto(public_socket, syn_ack, BUFFER_SIZE, 0, (struct sockaddr *) &public, public_size);
            test_error(syn_ack_size, "[-] \"SYN-ACK\" transmission error\n");

            // ACK RECEPTION

            memset(ack, 0, sizeof(ack));
            ack_size = recvfrom(public_socket, ack, BUFFER_SIZE, 0, (struct sockaddr *) &public, &public_size);
            test_error(ack_size, "[-] recvfrom error\n");

            if(memcmp(ack, "ACK", 3) != 0)
            {
                perror("[-] \"ACK\" reception error\n");
                return 0;
            }
            
            // CONNECTION ESTABLISHED
        }
        printf("Connection established: SYN = %s, SYN-ACK = %s, ACK = %s\n", syn, syn_ack, ack);

        multi = fork();

        if(multi == 0)
        {
            // REQUEST AND FILE OPENING _________________________________________________________________________________________________________________________________________________________________________________________

            memset(req, 0, BUFFER_SIZE);
            req_size = recvfrom(private_socket, req, BUFFER_SIZE, 0, (struct sockaddr *) &private, &private_size);
            test_error(req_size, "[-] File request reception error\n");
            printf("File requested: %s\n", req);
            
            // FILE OPENING

            FILE* file;
            file = fopen(req, "rb");
            if(file == NULL)
            {
                printf("[-] Unable to open requested file\n");
                exit(1);
            }

            // FILE SIZE

            fseek(file, 0L, SEEK_END);
            int file_size =  ftell(file);
            printf("File size: %d bytes\n", file_size);
            rewind(file);

            // LOAD FILE INTO LARGE BUFFER 

            memset(large_buffer, 0, sizeof(large_buffer));
            fread(&large_buffer, 1, file_size, file);
            fclose(file);

            char* sequence_number;
            int last_ack = 0;
            int previous_ack = 0;
            int last_sequence_number = file_size/(BUFFER_SIZE-6) + 1; // +1 for the remainder of the file
            int window_size = 60;
            int final_sequence_size = file_size - ((last_sequence_number - 1) * (BUFFER_SIZE - 6)) + 6;

            // TIMER START

            long int start_time = clock();

            // THREAD SETUP
            
            struct ack_thread_args *thread_args = malloc(sizeof(struct ack_thread_args));
            thread_args->thread_multi_ack_size = ack_size;
            thread_args->thread_private = private;
            thread_args->thread_private_socket = private_socket;
            thread_args->thread_private_size = private_size;
            thread_args->thread_window_size = window_size;

            ack_array_setup(last_sequence_number);

            // RUN THREAD
            
            pthread_t receive_thread;

            if(pthread_create(&receive_thread, NULL, ack_receive, (void *) thread_args) == -1)
            {
                perror("[-] Thread creation error.\n");
                return EXIT_FAILURE;
            }
            
            // FILE TRANSMISSION _________________________________________________________________________________________________________________________________________________________________________________________

            while(last_ack != last_sequence_number)
            {
                if(last_ack + window_size < last_sequence_number)
                {
                    int i = last_ack + 1;
                    while (i <= last_ack + window_size)
                    {
                        memset(msg, 0, BUFFER_SIZE);
                        sequence_number = pad_sequence_number(i);
                        memcpy(&msg[0], sequence_number, 6);
                        memcpy(&msg[6], &large_buffer[(i - 1) * (BUFFER_SIZE - 6)], BUFFER_SIZE - 6);
                        msg_size = sendto(private_socket, msg, BUFFER_SIZE, 0, (struct sockaddr *) &private, private_size);
                        i++;
                    }
                }
                
                if(last_ack + window_size >= last_sequence_number)
                {
                    int i = last_ack + 1;
                    while(i < last_sequence_number)
                    {
                        memset(msg, 0, BUFFER_SIZE);
                        sequence_number = pad_sequence_number(i);
                        memcpy(msg, sequence_number, 6);
                        memcpy(msg+6, &large_buffer[(i - 1) * (BUFFER_SIZE - 6)], BUFFER_SIZE - 6);
                        msg_size = sendto(private_socket, msg, BUFFER_SIZE, 0, (struct sockaddr *) &private, private_size);
                        i++;
                    }

                    memset(msg, 0, BUFFER_SIZE);
                    sequence_number = pad_sequence_number(last_sequence_number);
                    memcpy(msg, sequence_number, 6);
                    memcpy(msg+6, &large_buffer[(last_sequence_number - 1) * (BUFFER_SIZE - 6)], final_sequence_size);
                    msg_size = sendto(private_socket, msg, final_sequence_size, 0, (struct sockaddr *) &private, private_size);
                }
                
                {
                    previous_ack = last_ack;
                    last_ack = thread_args->thread_return_last_ack;

                    if(previous_ack == last_ack)
                    {
                        last_ack++;
                    }
                }
            }

            // END _________________________________________________________________________________________________________________________________________________________________________________________

            // TIMER END

            long int end_time = clock();
            float duration = (float) ((end_time - start_time)/CLOCKS_PER_SEC);

            printf("Speed (kb/s): %f\n", (float) (file_size/(1024 * duration)));

            memset(msg, 0, BUFFER_SIZE);
            sprintf(msg, "FIN");

            for(int i = 0; i < 10; i++)
            {
                end_size = sendto(private_socket, msg, BUFFER_SIZE, 0, (struct sockaddr *) &private, private_size);
            }

            test_error(end_size, "[-] \"FIN\" transmission error\n");
            close(private_socket);
            memset(syn_ack, 0, BUFFER_SIZE);
            main_loop = 0;
            break;
        }
    }
    close(public_socket);
    exit(1);
}