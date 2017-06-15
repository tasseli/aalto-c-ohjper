/*
 ============================================================================
 Name        : Kolmio.c
 Author      : Mikael Nenonen - k90390
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

#include <stdio.h>

void draw_triangle(int size) {
	for (int j=0; j<size; j++) {
		for (int i=0; i<size; i++) {
			if (size-i-1>j) {
				printf(".");
			}
			else
				printf("#");
		}
		printf("\n");
	}
}

int main(void) {
	int input = 0;
	scanf("%d", &input);
	draw_triangle(input);
	return 0;
}

//0,0		1,0		2,0
//0,1		1,1		2,1
//0,2		1,2		2,2
