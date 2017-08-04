#include <stdio.h>
#include <string.h>

// Mikael Nenonen k90390
// 2017-08-04

int dump_hex(const char *filename) {
  FILE* f;
  f = fopen(filename, "r");
  if(!f)
    return -1;
  int got, read=0;
  while(!feof(f)) {
    got = fgetc(f);
    if(got == EOF)
      break;
    read++;
    printf("%02x ", got);
    if(read != 0 && read % 16 == 0)
      printf("\n");
  }
  fclose(f);
  return read;
}
