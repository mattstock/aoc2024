#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

char *map, *scratch;
unsigned int mapsize;
unsigned int cols;
unsigned int rows;

struct coord {
  int x;
  int y;
};

int coord2pos(int x, int y) {
  return y*(cols+1)+x;
}

struct coord *pos2coord(int x) {
  struct coord *foo = malloc(sizeof(struct coord));

  foo->y = x/(cols+1);
  foo->x = x%(cols+1);
  return foo;
}

int yodel(int pos, char val) {
  struct coord *here;
  int score = 0;
  int x, y, foo;

  here = pos2coord(pos);
  x = here->x;
  y = here->y;
  free(here);

  if (map[pos] != val) {
    return 0;
  }
  if (map[pos] == '9') {
    printf("[%d, %d]\n", x, y);
    scratch[pos] = '*';
    return 1;
  }
  // Need to recurse for each valid cardinal direction!
  scratch[pos] = 'a'-'0'+val;
  
  // N
  if (y-1 >= 0) {
    foo = yodel(coord2pos(x, y-1), val+1);
    score += foo;
  }
  // S
  if (y+1 <= rows) {
    foo = yodel(coord2pos(x, y+1), val+1);
    score += foo;
  }
  // W
  if (x-1 >= 0) {
    foo = yodel(coord2pos(x-1, y), val+1);
    score += foo;
  }
  // E
  if (x+1 <= cols) {
    foo = yodel(coord2pos(x+1, y), val+1);
    score += foo;
  }
  return score;
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
  map = malloc(5000);

  fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    printf("Pick a real file!\n");
    exit(1);
  }

  mapsize = read(fd, map, 5000);
  map[mapsize] = '\0';
  scratch = malloc(mapsize+1);
  strcpy(scratch, map);
  close(fd);

  // size of things
  cols = (strchr(map, '\n')-map);
  rows = strlen(map)/(cols+1);

  printf("size is %u, %u\n", cols, rows);
  
  count = 0;
  for (int i=0; i < mapsize; i++) {
    if (map[i] != '0')
      continue;
    struct coord *th = pos2coord(i);
    printf("Found trailhead at %d, %d\n", th->x, th->y);
    strcpy(scratch, map);
    printf("trailhead total is %d\n", yodel(i, '0'));
    printf(scratch);
  }
  
  printf("paths = %d\n", count);
  
  free(map);
  exit(0);
}
