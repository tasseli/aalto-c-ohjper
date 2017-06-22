//
//  taulukkoharjoittelua.c
//  
//
//  Nenonen Mikael - k90390
//  15/06/17.
//
//

#include "taulukkoharjoittelua.h"
#include <stdio.h>

int array_sum(int *array, int count) {
    int sum = 0;
    for (int i = 0; i < count; ++i) {
        sum += array[i];
    }
    return sum;
}

int array_reader(int *vals, int n) {
    char line[0];
    scanf("%s", &line);
    printf(line);
    //for (int i = 0; i < n; ++i) {
        
    //}
    return 60;
}

int main(void) {
    int vals[] = {0};
	vals[0] = array_reader(vals, 1);
    //printf();
}
