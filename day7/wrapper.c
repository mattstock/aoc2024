#include <stdio.h>
#include <stdlib.h>

extern int consider(int, int *);

int main(int argc, char **argv) {
  FILE *fp;
  char str[60];
  int solution = 0;
  
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
    int total, count;
    int *vals = malloc(sizeof(int)*40);
    

    fgets(str, 60, fp);
    total = strtol(str, &next, 10);
    stub = next+1;
    while (*stub != '\0' && *stub != '\n') {
      vals[count] = strtol(stub, &next, 10);
      stub = next;
      count++;
    } 
    solution += consider(total, vals);
  }
  fclose(fp);
  printf("Solution sum = %d\n", solution);
  exit(0);
}
