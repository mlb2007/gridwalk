CC=gcc
CPP=g++
CFLAGS=-g -Wall
LDFLAGS=

all: monkey.o
	${CPP} ${LDFLAGS} -o monkeyTest -lm $<

%.o: %.cpp Makefile
	${CPP} ${CFLAGS} -c $<

clean:
	rm -f *.d *.o monkeyTest
