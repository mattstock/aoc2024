CC = cc
CFLAGS = -mcpu=ultrasparc

all: day7

day7: wrapper.o day7.o
	$(CC) -o $@ wrapper.o day7.o

day7.o: day7.S

wrapper.o: wrapper.c

clean:
	rm -f *.o *~ day7 *.core
