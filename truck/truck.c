#include <stdio.h>
#include <stdlib.h>

// Mikael Nenonen k90390
// 2017-07-10

struct truck{
  // Have truck data
}
typedef struct truck TR;

TR create_truck() {
  TR* trp = (TR) malloc(sizeof(TR));
  // Create a new truck in &trp
  return trp;
}

void print_truck(TR) {
  // Print truck data
}

int main(void) {

  return 0;
}