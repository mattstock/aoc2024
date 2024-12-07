#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

// this is the core in assembly
char guard();

char *map;

extern unsigned char dir;
extern unsigned cols, rows, pos;

int main(int argc, char **argv) {
  int fd;
  ssize_t s;
  int steps;
  
  if (argc != 2) {
    printf("%s <inputfile>\n", argv[0]);
    exit(1);
  }

  // whatever
  map = malloc(30000);

  fd = open(argv[1], O_RDONLY);
  s = read(fd, map, 30000);
  map[s] = '\0';
  close(fd);

  steps = guard();
  printf("dir = %u, pos = %u, and size is (%u, %u)\n", dir, pos, rows, cols);
  exit(0);
}
