#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int mapsize;
char *map;

int cols, rows, pos;

void learnstuff() {
  int i=0;
  
  cols = 0;
  rows = 0;

  while (map[i] != '\0') {
    switch (map[i]) {
    case '^':
      pos = i;
      break;
    case '\n':
      if (!cols)
	cols = i;
      rows++;
      break;
    }
    i++;
  }
}


void guard() {
  int done = 0;
  int steps = 0;
  int cons;
  
  learnstuff();
  printf("pos = %d, (%d, %d)\n", pos, cols, rows);
  
  while (!done) {
    switch (map[pos]) {
    case '^':
      cons = pos - (cols+1);
      if (cons < 0) {
	map[pos] = 'X';
	done = 1;
      } else {
	if (map[cons] == '#') {
	  map[pos] = '>';
	} else {
	  map[pos] = 'X';
	  map[cons] = '^';
	  pos = cons;
	}
      }
      break;
    case '>':
      cons = pos + 1;
      if (map[cons] == '\n' || map[cons] == '\0') {
	map[pos] = 'X';
	done = 1;
      } else {
	if (map[cons] == '#') {
	  map[pos] = 'v';
	} else {
	  map[pos] = 'X';
	  map[cons] = '>';
	  pos = cons;
	}
      }
      break;
    case 'v':
      cons = pos + (cols+1);
      if (cons > mapsize) {
	map[pos] = 'X';
	done = 1;
      } else {
	if (map[cons] == '#') {
	  map[pos] = '<';
	} else {
	  map[pos] = 'X';
	  map[cons] = 'v';
	  pos = cons;
	}
      }
      break;
    case '<':
      cons = pos - 1;
      if (cons < 0) {
	map[pos] = 'X';
	done = 1;
      }
      if (map[cons] == '\n') {
	map[pos] = 'X';
	done = 1;
      } else {
	if (map[cons] == '#') {
	  map[pos] = '^';
	} else {
	  map[pos] = 'X';
	  map[cons] = '<';
	  pos = cons;
	}
      }
      break;
    default:
      printf("something bad happened\n");
      exit(1);
    }
  }
}

int countX() {
  int x;

  for (int i=0; i < mapsize; i++)
    if (map[i] == 'X')
      x++;
  return x;
}

int main(int argc, char **argv) {
  int fd;
  
  if (argc != 2) {
    printf("%s <inputfile>\n", argv[0]);
    exit(1);
  }

  // whatever
  map = malloc(30000);

  fd = open(argv[1], O_RDONLY);
  mapsize = read(fd, map, 30000);
  map[mapsize] = '\0';
  close(fd);

  guard();
  printf("steps = %d\n", countX());
  exit(0);
}
