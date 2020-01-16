CC = gcc
CFLAGS = -Wall
LDFLAGS = -pthread -lpthread
TARGET = serveur1-H4M4C serveur-test

SRC=$(TARGET:=.c)
OBJ=$(SRC:.c=.o)
DEP=$(SRC:.c=.dep)
TEX=$(SRC:.c=.tex)

all: depend ${TARGET}

%.o: %.c
	${CC} -c ${CFLAGS} $< $(LDFLAGS)

%: %.o
	${CC} $< -o $@ $(LDFLAGS)

clean:
	-rm -f *.o ${BIN} ${TEX} ${DEP} *~ ${TARGET}
	clear

depend: ${DEP}

%.dep:	%.c
	$(CC) -MM -MF $@ $<

-include *.dep
