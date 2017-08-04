#include <stdio.h>
#include <string.h>

// Mikael Nenonen k90390
// 207-08-04

int line_count(const char *filename) {
  FILE* f = fopen(filename, "r");
  if(!f)
    return -1;
  int firstchar = fgetc(f);
  if(firstchar == EOF)
    return 0;
  int count=0;
  if((char)firstchar == '\n')
    count++;
  
  char line[1000] = "";
  while(fgets(line, 1000, f) != NULL) {
    count++;
  }
  return count;
}

int word_count(const char *filename) {
  
  return 0;
}
