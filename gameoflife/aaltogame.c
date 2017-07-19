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
	int j;
	for(j=0; j<a->ysize; j++) {
		free(a->cells[j]);
	}
	free(a->cells);
	free(a);
}

struct coords {
	unsigned int x;
	unsigned int y;
}; 

struct coords rand_coords(unsigned int xsize, unsigned int ysize) {
	struct coords newcoords;
	newcoords.x = rand() % xsize;
	newcoords.y = rand() % ysize;
	return newcoords;
}

void initArea(Area *a, unsigned int n) {
	for(;n>0;n--) {
		while(1) {
			struct coords trying;
			trying = rand_coords(a->xsize, a->ysize);
			if(a->cells[trying.y][trying.x] == DEAD) {
				a->cells[trying.y][trying.x] = ALIVE;
				break;
			}
		}
	}
}

void printArea(const Area *a) {
	int j, i;
	for(j=0; j<a->ysize; j++) {
		for(i=0; i<a->xsize; i++) {
			if(a->cells[j][i] == ALIVE)
				printf("*");
			if(a->cells[j][i] == DEAD)
				printf(".");
		}
		printf("\n");
	}
}

void tick(Area *a) {
	;
}
