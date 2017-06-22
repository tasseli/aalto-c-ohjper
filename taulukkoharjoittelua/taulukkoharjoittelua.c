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
	int i=0;
    while(1) {
	    int result = scanf("%d", &vals[i]);
		++i;
		if(result == 0) 
			break;
	}
	return i;
}

int main(void) {
    int vals[] = {33, 35, 36};
	int vals2[20] = {};
	int arvoja = array_reader(vals2, 20);
	//char my_sign = (char)array_sum(vals, 3);
	//printf("heis %c %d \n", my_sign, my_sign);
	
	int valarray[] = { 10, 100, 1000 };
	int ret = array_sum(valarray, 3);
	printf("Sum %d\n", ret);
	printf("Array_reader says %d\n", arvoja);
	printf("%d %d %d %d\n", vals2[0], vals2[1], vals2[2], vals2[3]);
}
