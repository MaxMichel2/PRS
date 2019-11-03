CC=gcc
CFLAGS=-Wall

TARGET = tcp_client1 tcp_server
#TARGET = tcp_client tcp_client1 tcp_client2 tcp_server tcp_server1 tcp_server2
#SRC=tcp_client.c tcp_server.c
SRC=$(TARGET:=.c)
OBJ=$(SRC:.c=.o)
DEP=$(SRC:.c=.dep)
TEX=$(SRC:.c=.tex)

all: depend ${TARGET}


%.o: %.c
	${CC} -c ${CFLAGS} $<


%: %.o
	${CC} $< -o $@



clean:
	-rm -f *.o ${BIN} ${TEX} ${DEP} *~ ${TARGET}

depend: ${DEP}

%.dep:	%.c
	$(CC) -MM -MF $@ $<

-include *.dep

tar:
	cd ..; tar cvf TD6-code.tar code/Makefile code/tcp_client1.c

tar-sol: clean
	cd ..; tar cvf TD6-sol.tar code/*
