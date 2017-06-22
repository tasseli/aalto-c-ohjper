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
    char line[120];
	printf("Anna lukuja.\n");
    int result = scanf("%s", &line);
	printf(line);
    if(result) {
	} else {
	}
	printf(line);
    //for (int i = 0; i < n; ++i) {
        
    //}
    return 4;
}

int main(void) {
    int vals[] = {33, 35, 36};
	vals[0] = array_reader(vals, 3);
	char my_sign = (char)array_sum(vals, 3);
	printf("heis %c %d \n", my_sign, my_sign);
	
	int valarray[] = { 10, 100, 1000 };
	int ret = array_sum(valarray, 3);
	printf("Sum %d", ret);
}
