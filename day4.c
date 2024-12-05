#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *board;
int cols = -1;

char magic[] = "XMAS";

// 0 1 2
// 3   4
// 5 6 7
// Calculate index for an adjacent grid position
int poslook(int index, int dir) {
  int new;

  // Corner cases are the devil
  if (index%cols == 0) {
    if (dir == 0 || dir == 3 || dir == 5)
      return -1;
  }
  if (index%cols == cols-1) {
    if (dir == 2 || dir == 4 || dir == 7)
      return -1;
  }

  // I probably can ignore these, but eh
  if (index/cols == 0) {
    if (dir == 0 || dir == 1 || dir == 2)
      return -1;
  }
  if (index+cols > strlen(board)) {
    if (dir == 5 || dir == 6 || dir == 7)
      return -1;
  }
  
  switch (dir) {
  case 0:
    new = index-cols-1;
    break;
  case 1:
    new = index-cols;
    break;
  case 2:
    new = index-cols+1;
    break;
  case 3:
    new = index-1;
    break;
  case 4:
    new = index+1;
    break;
  case 5:
    new = index+cols-1;
    break;
  case 6:
    new = index+cols;
    break;
  case 7:
    new = index+cols+1;
    break;
  }
  if (new < 0)
    return -1;
  if (new > strlen(board))
    return -1;
  return new;
}

// For a given index into the magic string, look for vectors in the direction.
// Return the number of successful matches.
int enlightenment(int index, int pos, int dir) {
  // check null condition
  if (index == strlen(magic)-1) {
    return magic[index] == board[pos];
  }

  char next = magic[index+1];
  int hop = poslook(pos, dir);
  if (hop == -1) {
    printf("dead end dir = %d\n", dir);
    return 0;
  }
  printf("looking at dir %d (%d, %d)\n", dir, hop%cols, hop/cols);
  if (next == board[hop]) { // recurse!
    printf("Found %c\n", next);
    return enlightenment(index+1, hop, dir);
  }
  return 0;
}


int main() {
  int s = 0;
  int count = 0;
  char ch;
  
  board = malloc(140*200); // close enough
  
  while (read(STDIN_FILENO, &ch, 1) > 0) {
    if (ch == '\n') {
      if (cols == -1)
	cols = s;
      continue;
    }
    board[s++] = ch;
  }
  board[s] = '\0';
  printf("columns == %d\n", cols);
  
  // Walk though each grid position for state 0
  for (int i=0; i < strlen(board); i++) {
    if (board[i] == magic[0]) {
      printf("Found a %c at %d\n", magic[0], i);
      for (int dir=0; dir < 8; dir++)
	count += enlightenment(0,i,dir);
    }
  }
  printf("Total strings matching %d\n", count);
  exit(0);
}
