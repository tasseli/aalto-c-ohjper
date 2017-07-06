/*
 ============================================================================
 Name        : vektorifunktio.c
 Author      : Mikael Nenonen - k90390
 Version     :
 Copyright   : 
 Description : Funktio vectorlength laskee annetun kolmiulotteisen vektorin pituuden
 ============================================================================
 */

#include <stdio.h>
#include <math.h>

double vectorlength(double x, double y, double z) {
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

int main(void) {
	printf("Vektorin pituus on %f", vectorlength(2, 5, 4));
	return 0;
}
