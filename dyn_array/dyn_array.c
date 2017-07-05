#include <stdio.h>
#include <stdlib.h>

// Mikael Nenonen k90390
// 2017-07-05

int *dynamic_reader(unsigned int n) {
  int *p = (int *) malloc(n*sizeof(int));
  if(p) { // allocation worked
    int i;
    for(i=0; i<n; i++) {
      scanf("%d", p);
      p++;
    }
    return p;
  }
  return 0;
}

int *insert_into_array(int *arr, unsigned int num, int newval) {
  return 0;
}

int main(void) {
  int *p = dynamic_reader(3);
  if(!p)
    return 1;
  return 0;
}
