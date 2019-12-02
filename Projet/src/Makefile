CC = gcc
CFLAGS = -Wall
TARGET = serveur1-H4M4C

SRC=$(TARGET:=.c)
OBJ=$(SRC:.c=.o)
DEP=$(SRC:.c=.dep)
TEX=$(SRC:.c=.tex)

all: depend ${TARGET}
	clear

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
