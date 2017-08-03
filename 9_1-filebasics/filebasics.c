#include <stdio.h>
#include <stdlib.h>
#include "filebasics.h"

// Mikael Nenonen k90390
// 2017-08-03

int print_file(const char *filename) {
  FILE *f = fopen(filename, "r");
  if (!f) {
    fprintf(stderr, "Opening file failed\n");
    exit(EXIT_FAILURE);  // ends program immediately (in stdlib)
  }
  int length = 0;
  while(1) {
    int got = fgetc(f);
    if(got == EOF)
      return -1;
    length++;
    printf("%c", (char)got);
  }
  fclose(f);
  return length;
}

char *difference(const char* file1, const char* file2) {
  return 0;
}
