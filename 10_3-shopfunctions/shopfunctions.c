#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shopfunctions.h"

// Mikael Nenonen k90390
// 2017-08-10

int compareAlpha(const void* a, const void* b) {
  
  return 0;
}

int compareNum(const void* a, const void* b) {
  
  return 0;
}

Product* findProduct(Product* p_array, const char* searchkey, int (*cmp)(const void*, const void*)) {
  return (Product*)bsearch(searchkey, p_array, sizeof(p_array)/sizeof(Product), sizeof(Product), cmp);
}
