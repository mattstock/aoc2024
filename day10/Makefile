CC = cc
CFLAGS = -mcpu=ultrasparc

all: day10

day10: wrapper.o day10.o
	$(CC) -o $@ wrapper.o day10.o

day10.o: day10.S

wrapper.o: wrapper.c

clean:
	rm -f *.o *~ day10 *.core
