CC = cc
CFLAGS = -mcpu=ultrasparc

all: day9

day9: wrapper.o day9.o
	$(CC) -o $@ wrapper.o day9.o

day9.o: day9.S

wrapper.o: wrapper.c

clean:
	rm -f *.o *~ day9 *.core
