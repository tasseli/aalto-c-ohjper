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
  strcpy(uus.name, name);
  strcpy(uus.attack_style, a_style);
  uus.hp = hp;
  return 1;
}

struct commandline tokenize(char *merkkijono) {
  struct commandline cline;
  cline.command = (char)tolower(merkkijono[0]);
  cline.correct = 1;
  printf("Tokenized! %d\n", cline.correct);
  return cline;
}

char * tokens_to_string(struct commandline cmd) {
  char *returned = malloc(166);
  returned[0] = cmd.command;
  returned[1] = ' ';
  strcpy(&returned[2], cmd.supplement_1);
  returned[83] = ' ';
  strcpy(&returned[84], cmd.supplement_2);
  returned[165] = '\0';
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
  case 'a':
    printf("%s\nPituus: %d\n", command, sizeof(merkkijono));
    break;
  default:
    ;
  }
    
  free(command);
  printf("Free ran.");
  return 0;
}
