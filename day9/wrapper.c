#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

unsigned char *map;
unsigned char *paint;
unsigned int mapsize;

extern void antiseek();
extern int yoff(unsigned char *pos1, unsigned char *pos2);
extern int xoff(unsigned char *pos1, unsigned char *pos2);

extern unsigned int cols, rows;

// so much easier to do this in C!
void debugchat(unsigned char *a, unsigned char *b) {
  printf("match %c (%d, %d) -> (%d, %d)\n",
	 *a,
	 xoff(map, a), yoff(map, a),
	 xoff(map, b), yoff(map, b));
  printf("  offset (%d, %d)\n", xoff(map,b)-xoff(map,a), yoff(map,b)-yoff(map,a));
}

void printmap() {
  printf("%s", paint);
}

int main(int argc, char **argv) {
  int fd;
  int count = 0;
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

  antiseek();

  printf("%s\n", paint);

  
  for (int i=0; i < mapsize; i++)
    count += (paint[i] == '#');

  printf("antinodes = %d\n", count);
  free(map);
  free(paint);
  exit(0);
}
