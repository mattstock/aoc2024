CC = cc

all: day6

day6: wrapper.o day6.o
	$(CC) -o day6 wrapper.o day6.o

day6.o: day6.S

wrapper.o: wrapper.c

clean:
	rm -f *.o *~ day6 *.core
