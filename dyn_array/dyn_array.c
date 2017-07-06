#include <stdio.h>
#include <stdlib.h>

// Mikael Nenonen k90390
// 2017-07-05

int *dynamic_reader(unsigned int n) {
  int *p = (int *) malloc(n*sizeof(int));
  int *copy = p;
  if(p) { // allocation worked
    int i;
    for(i=0; i<n; i++) {
      scanf("%d", p);
      p++;
    }
    return copy;
  }
  return 0;
}

int *insert_into_array(int *arr, unsigned int num, int newval) {
  int *p = (int *) realloc(arr, (num+1)*sizeof(int));
  p[num] = newval;
  return p;
}

int main(void) {
  int *p = dynamic_reader(3);
  if(!p)
    free(p);
    return 1;
  free(p);
  return 0;
}
