#include <stdio.h>
#include <stdlib.h>
#include "aaltogame.h"

// Mikael Nenonen k90390
// 2017-07-19

Area *createArea(unsigned int xsize, unsigned int ysize) {
	Area *area = malloc(sizeof(Area));
	area->xsize = xsize;
	area->ysize = ysize;
	int j,i;
	Status** rows = malloc(ysize*sizeof(Status*));
	area->cells = rows;
	for(j=0; j<ysize; j++) {
		Status* columns = malloc(xsize*sizeof(Status));
		area->cells[j] = columns;
		for(i=0; i<xsize; i++) {
			area->cells[j][i] = DEAD;
		}
	}
	return area;
}

void releaseArea(Area *a) {
	;
}

void initArea(Area *a, unsigned int n) {
	;
}

void printArea(const Area *a) {
	;
}

void tick(Area *a) {
	;
}
