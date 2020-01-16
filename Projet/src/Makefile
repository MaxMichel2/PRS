CC = gcc
CFLAGS = -Wall
TARGET = serv1 serv2 serv3 test

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
	clear

depend: ${DEP}

%.dep:	%.c
	$(CC) -MM -MF $@ $<

-include *.dep
