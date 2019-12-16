/*
    Simple udp server
*/
#include <stdio.h> //printf
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <assert.h>
#include <time.h>
#include <math.h>

#define BUFLEN 1494 //Max length of 
#define MSGLEN BUFLEN + 6 //Max length of the message we send 
#define ACKLEN 10  //The size of an ack message
#define MAX_ARRAY_SIZE 2000 //The max size of a chunk of data to be read and stored in buffer before sending it
#define MIN_WINDOW_SIZE 20

struct fragment{
	int segment;
	char message[BUFLEN];
};
typedef struct fragment FRAG;

struct sequence{
	char seq[6];
};
typedef struct sequence SEQ;

void die(char *s){
    perror(s);
    exit(1);
}

int get_ack_number(char ack_message[ACKLEN]){
	char number[ACKLEN - 3];
	int i = 0;
	for(i = 0; i < ACKLEN - 3; i++){
		number[i] = ack_message[i+3];
	}
	return atoi(number);
}

SEQ format_sequence(int n_seq){
	SEQ *seq = (SEQ*)malloc(sizeof(SEQ));
	char a[6];
	int count;
	int n = n_seq;
	if(n_seq > 999999){
		printf("Attention, sq numer over 6 bytes long\n");
	}
	while(n != 0)
    {
        n /= 10;
        ++count;
    }
    int i;
    for(i = 0; i < 6 - count; i++){
		a[i] = '0';
	}
    char b[count];
    sprintf(b, "%d", n_seq);
    strcat(a,b);
    for(i = 0; i < 6; i++){
		seq -> seq[i] = a[i];
	}
	return *seq;
}

float TCP_handshake(int s, char buf[BUFLEN], char message[BUFLEN], struct sockaddr_in si_other, int slen, int port){
	//recieve SYN
	memset(buf,'\0', BUFLEN);
	if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, (socklen_t *) &slen) == -1)
    {
            return -1;
    }
    message = "SYN\0";
    if(strcmp(message,buf) != 0 ){
			return -1;
	}
	printf("SYN recieved \n");
    char message2[BUFLEN] = {0};
	sprintf(message2, "SYN-ACK%d",port);
	
	clock_t start = clock();
	
    if (sendto(s, message2, strlen(message2) , 0 , (struct sockaddr *) &si_other, slen)==-1)
    {
            return -1;
    }
	printf("SYN-ACK sent \n");
	
	//recieve ACK
	memset(buf,'\0', BUFLEN);
	if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, (socklen_t *) &slen) == -1)
    {
            return -1;
    }
    clock_t end = clock();
    message = "ACK\0";
    if(strcmp(message,buf) != 0 ){
			return -1;
	}
	printf("ACK recieved \n");
	
	float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    return seconds;
}

FILE* init_file(char buf[BUFLEN], int commSocket){
        FILE *fp = NULL;
        char file[BUFLEN]="../src/";
        strcat(file, buf);
		fp = fopen(file,"rb");
		if(fp == NULL){
			close(commSocket);
			die("File does not exit");
		}
		printf("%s requested\n", buf);
		return fp;
}

int init_array(FRAG frag_array[], int no_fragments, size_t file_size, FILE *fp, int iteration){
	//Giving values to frag array
		FRAG *frag = (FRAG*)malloc(sizeof(FRAG));
		int j = 0;
		int i,segment,current;
		int last_size = MSGLEN;
		
		segment = iteration * MAX_ARRAY_SIZE; //number of the segment
		current = segment*BUFLEN; //current byte read
		for(i = 0 ; i < file_size; i = i + BUFLEN){
			if(segment > no_fragments - 1){
				i = file_size;
			}else{
				memset(frag -> message,'\0', BUFLEN);
				if(current + BUFLEN > file_size){
					segment++;
					last_size = file_size - current;
					if(fread(frag -> message,file_size - current,1,fp)<=0){
						printf("unable to copy file into buffer1\n");
						exit(1);
					}
				}else{
					segment++;
					if(fread(frag -> message,BUFLEN,1,fp)<=0){
						printf("unable to copy file into buffer2\n");
						printf("Fail in segment %d\n", segment);
						exit(1);
					}
					current = current + BUFLEN;
				}
				frag -> segment = segment;
				frag_array[j] = *frag;
				j++;
			}
		}	
		return last_size;
}

int send_slow_startIn(int commSocket,struct sockaddr_in si_other, int slen, int no_fragment, FRAG frag_array[], int index,int window_left, int* counter, int last_size, int* last_ack){
	
		if(index< no_fragment && window_left > 0){
			char long_message[MSGLEN];
			char ack_message[ACKLEN];
			int size = MSGLEN;
			
			memset(long_message,'\0', BUFLEN);
			SEQ *seq = (SEQ*)malloc(sizeof(SEQ));
			*seq = format_sequence(frag_array[index].segment);	
			strcat(long_message, seq->seq);
			memmove(long_message + 6, frag_array[index].message, size);
			
			if(index == no_fragment - 1){ //last segment
				size = last_size + 6; //+6 because of the 6 ints of the seq number
			}

			if (sendto(commSocket, long_message, size, 0 , (struct sockaddr *) &si_other, slen)==-1){
					die("sendto()");
			}
			printf("segment %d sent\n",frag_array[index].segment);
		
			send_slow_startIn(commSocket, si_other,  slen,  no_fragment,  frag_array, index +1 , window_left - 1, counter, last_size, last_ack);
			if(*counter < 1){
				if (recvfrom(commSocket, &ack_message, ACKLEN, 0, (struct sockaddr *) &si_other, (socklen_t *) &slen) == -1){
					*counter = *counter + 1;
					//return -1;
				}else{
					if(*last_ack < get_ack_number(ack_message)){
						*last_ack = get_ack_number(ack_message);
						printf("%s\n",ack_message);
					}
				}
			}
		}
	return 0;
}

int send_slow_start(int commSocket,struct sockaddr_in si_other, int slen, int no_fragment, FRAG frag_array[], int index, int window_left, int stop, int last_size, int* last_ack, int iteration){
	
	if(index< no_fragment && window_left > 0){
		char long_message[MSGLEN];
		char ack_message[ACKLEN];
		int size = MSGLEN;
		
		memset(long_message,'\0', BUFLEN);
		SEQ *seq = (SEQ*)malloc(sizeof(SEQ));
		*seq = format_sequence(frag_array[index].segment);	
		strcat(long_message, seq->seq);
		memmove(long_message + 6, frag_array[index].message, size);
		if(index == no_fragment - 1){ //last segment
				size = last_size + 6; //+6 because of the 6 ints of the seq number
				printf("This is the last one\n");
		}
		
		if (sendto(commSocket, long_message, size, 0 , (struct sockaddr *) &si_other, slen)==-1){
				die("sendto()");
		}
		printf("segment %d sent\n",frag_array[index].segment);
		int counter = 0;
		send_slow_startIn( commSocket,  si_other,  slen,  no_fragment,  frag_array, index +1 , window_left - 1, &counter, last_size, last_ack);
		
		if (recvfrom(commSocket, &ack_message, ACKLEN, 0, (struct sockaddr *) &si_other, (socklen_t *) &slen) == -1){
					//return -1;
		}else{
			if(*last_ack < get_ack_number(ack_message)){
				*last_ack = get_ack_number(ack_message);
				printf("%s\n",ack_message);
			}
		}
		
		if(*last_ack < index + MAX_ARRAY_SIZE*iteration + window_left){
			stop = 1;
			int counter = 0;
			
			if(*last_ack < no_fragment + MAX_ARRAY_SIZE*iteration){ //Fast retransmit
				while((counter < 2 )&& (*last_ack < index + MAX_ARRAY_SIZE*iteration + window_left)){
					int new_index = *last_ack - MAX_ARRAY_SIZE*iteration;
					
					memset(long_message,'\0', BUFLEN);
					SEQ *seq2 = (SEQ*)malloc(sizeof(SEQ));
					*seq2 = format_sequence(frag_array[new_index].segment);	
					strcat(long_message, seq2->seq);
					printf("segment to be resent %s \n",long_message);
					memmove(long_message + 6, frag_array[new_index].message, size);
					
					if(index == no_fragment - 1){ //last segment942

						size = last_size + 6; //+6 because of the 6 ints of the seq number
						printf("This is the last one\n");
					}
					
					if (sendto(commSocket, long_message, size, 0 , (struct sockaddr *) &si_other, slen)==-1){
							die("sendto()");
					}
					printf("segment %d resent\n",frag_array[new_index].segment);
					if (recvfrom(commSocket, &ack_message, ACKLEN, 0, (struct sockaddr *) &si_other, (socklen_t *) &slen) == -1){
						printf("I failed\n");
						//return -1;
					}else{
						if(*last_ack < get_ack_number(ack_message)){
							*last_ack = get_ack_number(ack_message);
							printf("%s\n",ack_message);
						}
					}
					counter++;
				}
			}
			window_left = window_left/2;
		}
		
	}
	if(index< no_fragment){
		if(stop == 0){
			return send_slow_start( commSocket,  si_other,  slen,  no_fragment,  frag_array, *last_ack - MAX_ARRAY_SIZE*iteration, window_left*2,0, last_size, last_ack, iteration);
		}else{
			return send_slow_start( commSocket,  si_other,  slen,  no_fragment,  frag_array, *last_ack - MAX_ARRAY_SIZE*iteration, window_left + 1,1, last_size, last_ack, iteration);
		}
	}else{
		return 0;
	}
	
}

int split_processus(int s, char buf[BUFLEN], char message[BUFLEN], struct sockaddr_in si_other, int slen, int port, float RTT){
	int pid = fork();
	if (!pid){
		printf("Using port: %d\n", s);
		int commSocket;
		FILE *fp = NULL;
		struct sockaddr_in si_comm;
		if ((commSocket=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
			die("socket");
		}
		
		memset((char *) &si_comm, 0, sizeof(si_comm));
     
		si_comm.sin_family = AF_INET;
		si_comm.sin_port = htons(port);
		si_comm.sin_addr.s_addr = htonl(INADDR_ANY);
		
		
		if( bind(commSocket , (struct sockaddr*)&si_comm, sizeof(si_comm) ) == -1){
			die("bind");
		}
		
		//receive file name
		if (recvfrom(commSocket, buf, BUFLEN, 0, (struct sockaddr *) &si_other, (socklen_t *) &slen) == -1){
            return -1;
		}
		fp = init_file(buf, commSocket); //Init file
		
		//Get file size
		fseek(fp,0,SEEK_END);
		size_t file_size=ftell(fp);
		fseek(fp,0,SEEK_SET);
		
		
		
		// Init of frag array
		int no_fragments;
		int array_size;
		if(file_size % BUFLEN != 0){
			no_fragments = file_size/BUFLEN + 1;
		}else{
			no_fragments = file_size/BUFLEN;
		}
		
		if(no_fragments > MAX_ARRAY_SIZE){ // in case file size exceeds the max size for an array
			array_size = MAX_ARRAY_SIZE;
		}else{
			array_size = no_fragments;
		}
		FRAG frag_array[array_size];
		int iteration = 0;
		int last_size = init_array(frag_array, array_size, file_size, fp, 0); // read file

		
		
		
		//Setting the Threshold
		struct timeval read_timeout;
		read_timeout.tv_sec = 0;
		read_timeout.tv_usec = (int)(0.3 * RTT * pow(10,9)); //Calculated RTT
		//read_timeout.tv_usec = 400000; //Fixed RTT
		setsockopt(commSocket, SOL_SOCKET, SO_RCVTIMEO, &read_timeout, sizeof read_timeout);
		setsockopt(commSocket, SOL_SOCKET, SO_SNDTIMEO, &read_timeout, sizeof read_timeout);
		
		//Increasing socket buffer size
		int bufsize = 402*1024;
		setsockopt(commSocket, SOL_SOCKET, SO_RCVBUF, &bufsize, sizeof(bufsize));
		setsockopt(commSocket, SOL_SOCKET, SO_SNDBUF, &bufsize, sizeof(bufsize));		
		
		//Actual sending of data
		int last_ack = 0;
		if(array_size == MAX_ARRAY_SIZE){ //The file is so big that it has to be read (and stored in buffer) in chunks
			while(iteration != -1){
				printf("This is iteration %d \n", iteration+1);
				send_slow_start( commSocket,  si_other,  slen,  array_size,  frag_array, 0, MIN_WINDOW_SIZE, 0, last_size, &last_ack, iteration);
				iteration++;	
				if(array_size + array_size*iteration < no_fragments){
					last_size = init_array(frag_array, array_size + array_size*iteration, file_size, fp, iteration); // read file
				}else{
					
					printf("This is last iteration!\n");
					//printf("Remember, total fragments is %d\n", no_fragments);
					int new_array_size = no_fragments - array_size*iteration;
					//printf("array size of %d!\n", new_array_size);
					
					FRAG frag_array2[new_array_size];
					last_size = init_array(frag_array2, new_array_size + array_size*iteration, file_size, fp, iteration); // read file
					send_slow_start( commSocket,  si_other,  slen,  new_array_size,  frag_array2, 0, MIN_WINDOW_SIZE, 0, last_size, &last_ack, iteration);
					iteration = -1;
				}
			}
		}else{ //The file is small enough to be read entirely in one chunk
			send_slow_start( commSocket,  si_other,  slen,  array_size,  frag_array, 0, MIN_WINDOW_SIZE, 0, last_size, &last_ack, iteration);
		}
		
		//Ending conection
		if (sendto(commSocket, "FIN", 12 , 0 , (struct sockaddr *) &si_other, slen)==-1){
				die("sendto()");
		}
		
		//Closing socket
		close(commSocket);
		
	}else{
		//Start new processus
		printf("Waiting for a handshake...\n");
		RTT = TCP_handshake(s, buf, message, si_other, slen, port - 1);
		printf("RTT time is: %f sec = %f usec\n", RTT, RTT * pow(10,9));
		printf("Handshake done...\n");
		split_processus(s, buf, message, si_other, slen, port -1, RTT);
	}
	return 0;
}

int main(int argc, char *argv[]){
    struct sockaddr_in si_me, si_other;
    //FRAG *frag = (FRAG*)malloc(sizeof(FRAG));
    int s, slen = sizeof(si_other);
    char buf[BUFLEN];
    char message[BUFLEN];
    int PORT;
    if (argc != 2){
		printf("Please select a port\n");
		exit(-1);
	}else{
		PORT = atoi(argv[1]);
	}
    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
    
    // zero out the structures
    memset((char *) &si_me, 0, sizeof(si_me));
     
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
    //bind sockets to ports
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }

     
    //TCP Handshake
    printf("Waiting for a handshake...\n");
    float RTT = TCP_handshake(s, buf, message, si_other, slen, PORT - 1);
    printf("RTT time is: %f sec = %f usec\n", RTT, RTT * pow(10,9));
    split_processus(s, buf, message, si_other, slen, PORT - 1, RTT);
    
    close(s);
    return 0;
}
