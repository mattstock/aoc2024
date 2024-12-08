CC = cc
#CFLAGS = -mcpu=ultrasparc

all: day8

day8: wrapper.o day8.o
	$(CC) -o $@ wrapper.o day8.o

day8.o: day8.S

wrapper.o: wrapper.c

clean:
	rm -f *.o *~ day8 *.core
