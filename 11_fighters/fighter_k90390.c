#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Mikael Nenonen k90390
// 2017-08-17 16:00

struct fighter{
  char name[80];
  char attack_style[32];
  int hp;
};
#define FIGHTER struct fighter

struct commandline{
  char command;
  char supplement_1[80];
  char supplement_2[80];
  int correct;
};

int new_fighter(char *name, char *a_style, int hp) {
  FIGHTER uus;
  printf("Name = %s\n", *name);
  strcpy(uus.name, name);
  printf("Copied. Name = %s\n", uus.name);
  strcpy(uus.attack_style, a_style);
  uus.hp = hp;
  return 1;
}

struct commandline tokenize(char *merkkijono) {
  struct commandline cline;
  int tokens = 0;
  if(merkkijono[0] != '\0' && merkkijono[1] == ' ') {
    cline.command = (char)toupper(merkkijono[0]);
    tokens++;

    char space[2] = " \0";
    if(merkkijono[2] != '\0') {
      strcpy(cline.supplement_1, strtok(&merkkijono[2], space));
      tokens++;
    }
  }
  if(
  strcpy(cline.supplement_2, strtok(NULL, space));
  cline.correct = 1;
  return cline;
}

char * tokens_to_string(struct commandline cmd) {
  char *returned = malloc(166);
  returned[0] = cmd.command;
  returned[1] = ' ';
  strcpy(&returned[2], cmd.supplement_1);
  char * space = strchr (&returned[2], (int)'\0');
  *space = ' ';
  strcpy(space+1, cmd.supplement_2);
  return returned;
}

int main(void) {
  char merkkijono[160];
  printf("Tervetuloa taistelupeliin (vaiheessa)!\n> ");
  fflush(stdout);
  fgets(merkkijono, sizeof(merkkijono), stdin);
  struct commandline cline;
  cline = tokenize(merkkijono);
  char* command = tokens_to_string(cline);
  switch(merkkijono[0]) {
  case 'A':
    printf("%s\nPituus: %d\n", command, sizeof(merkkijono));
    break;
  default:
    ;
  }
    
  free(command);
  return 0;
}
 
 /*
 Ideas for attack styles:
 - Harmful wish     1
 - Guilt trip       1
 - Growl            1
 - Shriek           1
 - Bite             2
 - Curse            2
 - Emasculate       2
 - Punch            3
 - Crush            3
 - Headbutt         4
 - Kick             5
 - Poison bite      7
 - Roundhouse kick  7
 - Stomp            8
 - Fire punch       10
 - Power throw      12
 - Defenestrate     15
 - Deorbit          35
 - Decimate         n*9/10
 - Decapitate       55
 */