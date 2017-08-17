#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mikael Nenonen k90390
// 2017-08-17 16:00

struct fighter{
  char name[160];
  char attack_style[32];
  int hp;
};
#define FIGHTER struct fighter

int new_fighter(char *name, char *a_style, int hp) {
  FIGHTER uus;
  strcpy(uus.name, name);
  strcpy(uus.attack_style, a_style);
  uus.hp = hp;
  return 1;
}

int main(void) {
  char merkkijono[160];
  printf("Tervetuloa taistelupeliin (vaiheessa)!\n> ");
  fflush(stdout);
  fgets(merkkijono, sizeof(merkkijono), stdin);
  switch(merkkijono[0]) {
  case 'A':
    if(1)
      ; // add monster
    else
      ; // herja
    break;
  default:
    ;
  }
    
  return 0;
}
