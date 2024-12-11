#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <inttypes.h>
#include <unistd.h>

struct rock {
  unsigned int ply;
  unsigned long v;
  struct rock *next;
};

unsigned long workqueue = 0;
unsigned long iterations = 25;

int digit_counts(unsigned long x) {
  int d = 1;
  while (x = x/10)
    d++;
  return d;
}
  
void blink(unsigned int ply, struct rock *idx) {
  unsigned long p;
  int d;
  struct rock *newrock;

  if (ply < idx->ply)
    return;
  
  // rule 0
  if (idx->v == 0) {
    idx->v = 1;
    return;
  }
  // rule even
  d = digit_counts(idx->v);
  if (!(d % 2)) {
    d /= 2;
    newrock = malloc(sizeof(struct rock));
    newrock->next = idx->next;
    newrock->ply = ply+1;
    idx->next = newrock;
    newrock->v = 0;
    p=1;
    while (d) {
      newrock->v += (idx->v % 10)*p;
      idx->v = idx->v / 10;
      p *= 10;
      d--;
    }
    workqueue++;
    return;
  }
  // rule 2024
  idx->v *= 2024;
}

int main(int argc, char **argv) {
  char rawline[100];
  int linesize;
  int fd;
  struct rock *tmprock, *lastrock;
  struct rock *row = NULL;
  char *idx, *idxnext;
  unsigned long count = 0;

  int val, e;

  if (argc != 3) {
    printf("%s <iterations> <inputfile>\n", argv[0]);
    exit(1);
  }

  iterations = strtol(argv[1], NULL, 10);
  
  fd = open(argv[2], O_RDONLY);
  if (fd == -1) {
    printf("Pick a real file!\n");
    exit(1);
  }

  linesize = read(fd, rawline, 100);
  rawline[linesize] = '\0';
  close(fd);

  idx = rawline;
  while (*idx != '\0' && *idx != '\n') {
    tmprock = malloc(sizeof(struct rock));
    tmprock->next = NULL;
    tmprock->ply = 0;
    tmprock->v = strtol(idx, &idxnext, 10);
    workqueue++;
    if (row == NULL)
      row = tmprock;
    else
      lastrock->next = tmprock;
    lastrock = tmprock;
    idx = idxnext;
  }

  // Depth first
  while (row != NULL) {
    for (int i=0; i < iterations; i++)
      blink(i, row);
    //    printf("work queue = %lu\n", workqueue);
    count++;
    workqueue--;
    lastrock = row;
    row=row->next;
    free(lastrock);
  }
  /*
  while (lastrock != NULL) {
    printf("%lu ", lastrock->v);
    lastrock=lastrock->next;
  }
  putchar('\n');
  */ 
  printf("got %lu\n", count);
	   
  exit(0);
}
