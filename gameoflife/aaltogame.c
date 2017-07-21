#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aaltogame.h"

// Mikael Nenonen k90390
// 2017-07-19

Area * create_area_pointer(unsigned int width, unsigned int height) {
  Area *newarea = malloc(sizeof(Area));
  newarea->xsize = width;
  newarea->ysize = height;
  int i,j;
  Status** rows = malloc(newarea->ysize*sizeof(Status*));
  newarea->cells = rows;
  for(j=0; j < newarea->ysize; j++) {
      Status* columns = malloc(newarea->xsize*sizeof(Status));
      newarea->cells[j] = columns;
  }
  return newarea;
}

Area *createArea(unsigned int xsize, unsigned int ysize) {
	Area *area = create_area_pointer(xsize, ysize);
	int j,i;
	for(j=0; j<ysize; j++) {
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
	int x;
	int y;
}; 

struct coords newCoords(int x, int y) {
	struct coords returnable;
	returnable.x = x;
	returnable.y = y;
	return returnable;
}

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

struct neighborCoords {
	struct coords surrounding[8];
};

void print_neighborcoords(struct neighborCoords printed) {
  int i;
  for(i=0; i<8; i++) {
    printf("i: %d, x: %d y: %d\n", i, printed.surrounding[i].x, printed.surrounding[i].y);
  }
}

struct neighborCoords legalNeighbors(int x, int y, unsigned int xsize, unsigned int ysize) {
	struct neighborCoords legal;
	int i;
	for(i=0;i<8;i++) {
		legal.surrounding[i].x = -1;
		legal.surrounding[i].y = -1;
	}
	if(x>0)
		legal.surrounding[0] = newCoords(x-1, y);
	if(y>0)
		legal.surrounding[1] = newCoords(x, y-1);
	if(x<xsize-1)
		legal.surrounding[2] = newCoords(x+1, y);
	if(y<ysize-1)
		legal.surrounding[3] = newCoords(x, y+1);
	if(y<ysize-1 && x<xsize-1)
		legal.surrounding[4] = newCoords(x+1, y+1);
	if(y<ysize-1 && x>0)
		legal.surrounding[5] = newCoords(x-1, y+1);
	if(y>0 && x<xsize-1)
		legal.surrounding[6] = newCoords(x+1, y-1);
	if(y>0 && x>0)
		legal.surrounding[7] = newCoords(x-1, y-1);
  print_neighborcoords(legal);
	return legal;
}

Status gameLogic(int neighborsAlive, Status current) {
	if(neighborsAlive == 3)
		return ALIVE;
	if(neighborsAlive > 3)
		return DEAD;
	if(neighborsAlive < 2)
		return DEAD;
	return current;
}

void tick(Area *a) {
  // Create b as a dynamic "empty copy" of a
  Area *b = create_area_pointer(a->xsize, a->ysize);
  // Use the game logic to create the next tick in b
  int l,m;
	for(m=0; m < a->ysize; m++) {
		for(l=0; l < a->xsize; l++) {
			int neighborsAlive=0;
			struct neighborCoords here;
			here = legalNeighbors(l, m, a->xsize, a->ysize);
			int k;
			for(k=0;k < 8;k++) {
				if(here.surrounding[k].x == -1 || here.surrounding[k].y == -1) {
					continue;
        }
				if(a->cells[here.surrounding[k].x][here.surrounding[k].y] == ALIVE) {
					neighborsAlive++;
        }
			}
			b->cells[l][m] = gameLogic(neighborsAlive, a->cells[l][m]);
		}
	}

  // Copy b to a
  int j,i;
  for(j=0; j<a->ysize; j++) {
      for(i=0; i<a->xsize; i++) {
          a->cells[j][i] = b->cells[j][i];
      }
  }
  
  releaseArea(b);
}
