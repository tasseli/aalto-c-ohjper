#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
  FILE* f = fopen(filename, "r");
  if(!f)
    return -1;
  int words = 0;
  char line[1000] = "";
  while(fgets(line, 1000, f) != NULL) {
    int i;
    int prev_was_space = 1;
    int prev_was_alpha = 0;
    for(i=0; i<1000 && line[i] != 0; i++) {
      // handle lines beginning with whitespace, and space sequences.
      if(prev_was_space == 1) {
        if(isspace((int)line[i]))
          continue;
      }
      // count a word as one only
      if(isalpha((int)line[i])) {
        if(prev_was_alpha == 0)
          words++;
        prev_was_alpha = 1;
        prev_was_space = 0;
      }
      if(isspace((int)line[i])) {
        prev_was_space = 1;
        prev_was_alpha = 0;
      }
    }
  }
  return words;
}
