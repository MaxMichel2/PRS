#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main()
{
    char buffer[6];
    char ack[9] = "ACK060015";
    sprintf(buffer, "SYN");

    if(memcmp(buffer, "SYN", 3) == 0)
    {
        printf("Both equal\n");
    }

    int val = atoi(&ack[3]);
    printf("Value: %d\n", val);
}

/*
union
{
    unsigned int integer;
    unsigned char byte[4];
} foo;

int main()
{
    foo.integer = 123456789;
    printf("%u %u %u %u\n", foo.byte[3], foo.byte[2], foo.byte[1], foo.byte[0]);
}
*/

/*
int main(void)
{
    char buff[1000];
    int bytes = read(0, buff, sizeof buff); // 0 is stdin's file descriptor 
    if (bytes > 0)
    {
        int i;
        for (i = 0; i < bytes; ++i)
        {
            printf("%d : %c\n", i, buff[i]);
        }
    }
    return 0;
}
*/