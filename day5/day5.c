#include <stdio.h>
#include <stdlib.h>

struct rule {
  int a;
  int b;
  struct rule *next;
};

struct update {
  unsigned *pages;
  int count;
  struct update *next;
};

struct rule *rules = NULL;
struct update *updates = NULL;

void read_rules(FILE *in) {
  struct rule *x, *lastptr;
  char rulebuf[10];
  char *nw;
  
  while (!feof(in)) {
    fgets(rulebuf, 10, in);
    if (rulebuf[0] == '\n')
      return;
    x = malloc(sizeof(struct rule));
    x->a = strtol(rulebuf, &nw, 10);
    x->b = strtol(++nw, NULL, 10);
    if (rules == NULL)
      rules = x;
    else
      lastptr->next = x;
    lastptr = x;
  }
  printf("Ran out of file before getting to the updates!\n");
}

struct update *parseLine(FILE *in) {
  struct update *x = malloc(sizeof(struct update));
  int slots = 10;
  int done = 0;
  char c;
  
  x->pages = reallocarray(NULL, sizeof(unsigned),slots);
  x->count = 0;
  while (!feof(in)) {
    // Sue me I'm lazy
    fscanf(in, "%u", &(x->pages[x->count++]));

    if (x->count  == slots) {
      slots += 10;
      x->pages = reallocarray(x->pages, sizeof(unsigned),slots);
    }
    c = fgetc(in);
    if (c == '\n')
      return x;
  }
  free(x);
  return NULL;
}

void read_updates(FILE *in) {
  struct update *x, *lastptr;

  while (!feof(in)) {
    x = parseLine(in);
    if (x == NULL)
      return;
    if (updates == NULL)
      updates = x;
    else
      lastptr->next = x;
    lastptr = x;
  }
}

int main(int argc, char *argv[]) {
  FILE *input;
  int middle_sum = 0;
  
  if (argc != 2) {
    printf("day5 <input file>\n");
    exit(1);
  }
  input = fopen(argv[1], "r");
  read_rules(input);
  read_updates(input);
  fclose(input);
  
  while (updates != NULL) {
    int fail = 0;

    // It's a onehot state machine
    for (struct rule *r = rules; (r != NULL) && !fail; r = r->next) {
      int look = 0;
      for (int i=0; (i < updates->count) && !fail; i++) {
	if (look == 0 && updates->pages[i] == r->b)
	  look = 1;
	if (look == 1 && updates->pages[i] == r->a)
	  fail = 1;
      }
    }
    if (!fail) {
      printf("middle page is %d\n", updates->pages[updates->count/2]);
      middle_sum += updates->pages[updates->count/2];
    }
    updates = updates->next;
  }
  printf("middle sum is %d\n", middle_sum);
  exit(0);
}

  
