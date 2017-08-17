#include <stdio.h>
#include <stdlib.h>

// Mikael Nenonen k90390
// 2017-08-17 16:00

struct fighter{
  char name[160] = "";
  char attack_style[32] = "";
  int hp = 1;
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
  fgets(merkkijono, sizeof(merkkijono), stdin);
  swich(merkkijono[0])
  case 'A':
    if(scanf() == 5)
      ; // add monster
    else
      ; // herja
    break;
  default:
    break;
    
  return 0;
}
