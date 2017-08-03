#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  FILE *f1 = fopen(file1, "r");
  FILE *f2 = fopen(file2, "r");
  if (!f1 || !f2) {
    fprintf(stderr, "Opening file failed\n");
    return 0;
  }
  char *s1, *s2;
  int bignumber = 1000;
  s1 = malloc(bignumber);
  s2 = malloc(bignumber);
  while(1) {
    s1 = fgets(s1, bignumber, f1);
    s2 = fgets(s2, bignumber, f2);
    if(s1 == 0 || s2 == 0)
      break;
    char *s1copy, *s2copy;
    s1copy = s1;
    s2copy = s2;
    int diff = 0;
    while(*s1copy) {
      if(!(*s1copy == *s2copy))
        diff = 1;
      if(*s2copy == 0)
        break;
      s1copy++, s2copy++;
    }
    if(*s2copy)
      diff = 1;
    if(diff) {
      char* dashes = "----";
      s1 = strcat(s1, dashes);
      s1 = strcat(s1, s2);
      free(s2);
      fclose(f1);
      fclose(f2);
      return s1;
    }
    s1++, s2++;
  }
  fclose(f1);
  fclose(f2);
  free(s1);
  free(s2);
  return 0;
}
