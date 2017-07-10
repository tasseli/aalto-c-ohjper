#include <stdio.h>
#include <stdlib.h>
#include "source.h"

// Mikael Nenonen k90390
// 2017-07-10

typedef struct truck TR;

TR create_truck(const char *name, double length, double weight, struct cargo crg) {
  // Create a new truck in &trp
  TR creation;
  creation.length = length;
  creation.weight = weight;
  creation.crg = crg;
  int i;
  for(i=0; i<31; i++) {
    creation.name[i] = name[i];
  }
  return creation;
}

void print_truck(const TR *car) {
  // Print truck data
}

int main(void) {
  char* name = (char *) malloc(31);
  char copied[] = "Muumibiili";
  int i = 0;
  while(copied[i]) {
    name[i] = copied[i];
    i++;
  }
  name[i] = copied[i];
  
  char* title = malloc(31);
  char copied2[] = "Vaapukkamehua";
  i = 0;
  while(copied2[i]) {
    title[i] = copied2[i];
    i++;
  }
  title[i] = copied2[i];
  struct cargo ekakargo;
  ekakargo.title = title;
  ekakargo.quantity = 3;
  ekakargo.weight = 4;
  
  create_truck(name, 1, 2, ekakargo);
  return 0;
}