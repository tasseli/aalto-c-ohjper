// Mikael Nenonen k90390
// 2017-07-24

#include <stdio.h>
#include "bits.h"

void bit_set(unsigned char* data, int idx) {
  int charpos = idx/8;
  int withincharpos = idx%8;
  data += charpos;
  if(withincharpos == 0)
    *data = *data | 0x80;
  if(withincharpos == 1)
    *data = *data | 0x40;
  if(withincharpos == 2)
    *data = *data | 0x20;
  if(withincharpos == 3)
    *data = *data | 0x10;
  if(withincharpos == 4)
    *data = *data | 0x8;
  if(withincharpos == 5)
    *data = *data | 0x4;
  if(withincharpos == 6)
    *data = *data | 0x2;
  if(withincharpos == 7)
    *data = *data | 0x1;
}

int bit_get(const unsigned char* data, int idx) {
}

void bit_unset(unsigned char* data, int idx) {
}

unsigned char bit_get_sequence(const unsigned char* data, int idx, int how_many) {
}

void print_byte(unsigned char b) {
}