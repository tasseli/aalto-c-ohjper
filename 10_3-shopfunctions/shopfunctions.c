#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shopfunctions.h"

// Mikael Nenonen k90390
// 2017-08-10

int compareAlpha(const void* a, const void* b) {
  return strcmp(((Product*)a)->name, ((Product*)b)->name);
}

int compareNum(const void* a, const void* b) {
  if(((Product*)a)->in_stock > ((Product*)b)->in_stock)
    return -1;
  if(((Product*)b)->in_stock > ((Product*)a)->in_stock)
    return 1;
  return compareAlpha(a, b);
}

Product* findProduct(Product* p_array, const char* searchkey, int (*cmp)(const void*, const void*)) {
  int i=0, count=0;
  while(p_array[0+i].name[0] != '\0') {
    count++;
    i++;
  }
  return (Product*)bsearch(searchkey, p_array, count, sizeof(Product), cmp);
}
