CC=gcc
CPP=g++
CFLAGS=-g -Wall
LDFLAGS=

all: gridwalk.o
	${CPP} ${LDFLAGS} -o gridwalkTest -lm $<

%.o: %.cpp Makefile
	${CPP} ${CFLAGS} -c $<

clean:
	rm -f *.d *.o gridwalkTest
