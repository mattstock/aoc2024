#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int consider(int, int, int, int *);

int main(int argc, char **argv) {
  FILE *fp;
  char str[60];
  unsigned solution = 0;
  
  if (argc != 2) {
    printf("%s <inputfile>\n", argv[0]);
    exit(1);
  }

  fp = fopen(argv[1], "r");
  if (fp == NULL) {
    printf("Pick a real file!\n");
    exit(1);
  }

  while (!feof(fp)) {
    char *next, *stub;
    unsigned total, count;
    int *vals = malloc(sizeof(int)*40);

    if (fgets(str, 60, fp) == NULL)
      break;
    total = strtol(str, &next, 10);
    stub = next+1;
    count = 0;
    while (*stub != '\0' && *stub != '\n') {
      vals[count] = strtol(stub, &next, 10);
      stub = next;
      count++;
    }
    if (consider(total, 0, count, vals))
      solution += total;
  }
  fclose(fp);
  printf("Solution sum = %u\n", solution);
  exit(0);
}
