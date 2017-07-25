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

void bit_unset(unsigned char* data, int idx) {
  int charpos = idx/8;
  int withincharpos = idx%8;
  data += charpos;
  if(withincharpos == 0)
    *data = *data & ~0x80;
  if(withincharpos == 1)
    *data = *data & ~0x40;
  if(withincharpos == 2)
    *data = *data & ~0x20;
  if(withincharpos == 3)
    *data = *data & ~0x10;
  if(withincharpos == 4)
    *data = *data & ~0x8;
  if(withincharpos == 5)
    *data = *data & ~0x4;
  if(withincharpos == 6)
    *data = *data & ~0x2;
  if(withincharpos == 7)
    *data = *data & ~0x1;
}

int bit_get(const unsigned char* data, int idx) {
  int charpos = idx/8;
  int withincharpos = idx%8;
  data += charpos;
  if(withincharpos == 0)
    return (*data & 0x80)/128;
  if(withincharpos == 1)
    return (*data & 0x40)/64;
  if(withincharpos == 2)
    return (*data & 0x20)/32;
  if(withincharpos == 3)
    return (*data & 0x10)/16;
  if(withincharpos == 4)
    return (*data & 0x8)/8;
  if(withincharpos == 5)
    return (*data & 0x4)/4;
  if(withincharpos == 6)
    return (*data & 0x2)/2;
  if(withincharpos == 7)
    return *data & 0x1;
  return -1; // Error
}

void print_byte(unsigned char b) {
  printf("%d%d%d%d%d%d%d%d\n", b/128, (b%128)/64, ((b%128)%64)/32, (b%128%64%32)/16, (b%128%64%32%16)/8, (b%128%64%32%16%8)/4, (b%128%64%32%16%8%4)/2, (b%128%64%32%16%8%4%2));
}

unsigned char bit_get_sequence(const unsigned char* data, int idx, int how_many) {
  data += idx/8;
  int i, read=0;
  unsigned char answer = 0x0;
  printf("idx: %d, how_many: %d\n", idx, how_many);
  for(i=idx%8; 8-i>0; i++) {
    printf("This is bit_get for 1 and i is %d, read %d\n", i, read);
    print_byte(answer);
    if(!read == 0)
      answer = answer << 1;
    print_byte(answer);
    printf("Reading with bit_get: %d\n", bit_get(data, i));
    if(bit_get(data, i))
      bit_set(&answer, 7);
    else
      bit_unset(&answer, 7);
    read++;
    if(read == how_many)
      return answer;
  }
  data++;
  for(; i-8<8; i++) {
    printf("This is bit_get for 2 and i is %d\n", i);
    printf("Answer now: %d\n", answer);
    answer = answer << 1;
    if(bit_get(data, i))
      bit_set(&answer, 7);
    else
      bit_unset(&answer, 7);
    read++;
    if(read == how_many)
      return answer;
  }
  return -1;
}
