#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "source.h"

// Mikael Nenonen k90390
// 2017-07-10

typedef struct truck TR;

void copy_name(char* pointer, const char* string) {
  int i = 0;
  while(string[i]) {
    pointer[i] = string[i];
    i++;
  }
  pointer[i] = string[i];
}

TR create_truck(const char *name, double length, double weight, struct cargo crg) {
  TR creation;
  creation.length = length;
  creation.weight = weight;
  creation.crg = crg;
  copy_name((char *) &creation.name, name);
  return creation;
}

void print_truck(const TR *car) {
  // Print truck data
  char nimi[31];
  strcpy(nimi, car->name);
  printf("%s\n", nimi);
}

int main(void) {
  char* name = (char *) malloc(31);
  copy_name(name, "Muumibiili");
  
  char* title = malloc(31);
  copy_name(title, "Vaapukkamehua");
  struct cargo first_cargo;
  first_cargo.title = title;
  first_cargo.quantity = 3;
  first_cargo.weight = 4;
  
  TR eka = create_truck(name, 1, 2, first_cargo);
  print_truck(&eka);
  return 0;
}