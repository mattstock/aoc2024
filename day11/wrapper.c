#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <inttypes.h>
#include <unistd.h>

struct rock {
  unsigned long v;
  struct rock *next;
};

void print_row(struct rock *idx) {
  while (idx != NULL) {
    printf("%d ", idx->v);
    idx = idx->next;
  }
  putchar('\n');
}

int digit_counts(int x) {
  int d = 1;
  while (x = x/10)
    d++;
  return d;
}
  
void blink(struct rock *idx) {
  unsigned long d,p;
  struct rock *newrock;

  print_row(idx);
  
  while (idx != NULL) {
    printf("examine %lu\n", idx->v);
    // rule 0
    if (idx->v == 0) {
      idx->v = 1;
      idx = idx->next;
      printf("rule 0\n");
      continue;
    }
    // rule even
    d = digit_counts(idx->v);
    if (!(d % 2)) {
      printf("rule even\n");
      d /= 2;
      printf("half is %d\n", d);
      newrock = malloc(sizeof(struct rock));
      newrock->next = idx->next;
      idx->next = newrock;
      newrock->v = 0;
      p=1;
      while (d) {
	printf("before %lu\n", idx->v);
	newrock->v += (idx->v % 10)*p;
	idx->v = idx->v / 10;
	p *= 10;
	d--;
	printf(" split %lu : %lu\n", idx->v, newrock->v);
      }
      idx = newrock->next;
      continue;
    }
    // rule 2024
    printf("rule 2024\n");
    idx->v *= 2024;
    idx = idx->next;
  }
}

int main(int argc, char **argv) {
  char rawline[100];
  int linesize;
  int fd;
  struct rock *tmprock, *lastrock;
  struct rock *row = NULL;
  char *idx, *idxnext;

  int val, e;

  if (argc != 2) {
    printf("%s <inputfile>\n", argv[0]);
    exit(1);
  }

  fd = open(argv[1], O_RDONLY);
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
    tmprock->v = strtol(idx, &idxnext, 10);
    if (row == NULL)
      row = tmprock;
    else
      lastrock->next = tmprock;
    lastrock = tmprock;
    idx = idxnext;
  }

  
  for (int i=0; i < 26; i++) {
    blink(row);
    print_row(row);
  }
  int count=0;
  while (row != NULL) {
    count++;
    row=row->next;
  }
  printf("rock count = %d\n", count);
  exit(0);
}
