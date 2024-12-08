#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

unsigned char *map;
unsigned char *paint;
unsigned int mapsize;

int main(int argc, char **argv) {
  int fd;
  
  char str[60];
  
  if (argc != 2) {
    printf("%s <inputfile>\n", argv[0]);
    exit(1);
  }

  // room for the map
  map = malloc(3000);

  fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    printf("Pick a real file!\n");
    exit(1);
  }

  mapsize = read(fd, map, 3000);
  map[mapsize] = '\0';
  paint = malloc(mapsize+1);
  paint[mapsize] = '\0';
  close(fd);

  
  free(map);
  exit(0);
}
