rm=/bin/rm -f
CC=gcc
DEFS=
INCLUDES=-I.
LIBS=

DEFINES= $(INCLUDES) $(DEFS)
CFLAGS= -std=c99 $(DEFINES) -O2 -g -Wall

all: ketje 

ketje: main.c
	$(CC) $(CFLAGS) -o ketje main.c $(LIBS)

clean:
	rm -f ketje
	rm -rf ketje.dSYM