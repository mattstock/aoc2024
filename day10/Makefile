CC = cc
CFLAGS = -mcpu=ultrasparc

all: aoc

aoc: wrapper.o
	$(CC) -o $@ wrapper.o

aoc.o: aoc.S

wrapper.o: wrapper.c

clean:
	rm -f *.o *~ aoc *.core
