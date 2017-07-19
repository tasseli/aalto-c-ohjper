#include <stdio.h>
#include "aaltogame.h"

// Mikael Nenonen k90390
// 2017-07-19

Area *createArea(unsigned int xsize, unsigned int ysize) {
	Area *area = malloc(sizeof(Area));
	area->xsize = xsize;
	area->ysize = ysize;
	int j,i;
	area->cells = Status* rows[ysize];
	for(j=0; j<ysize; j++) {
		area->cells[j] = Status columns[xsize];
		for(i=0; i<xsize; i++) {
			area->cells[j][i] = DEAD;
		}
	}
}
