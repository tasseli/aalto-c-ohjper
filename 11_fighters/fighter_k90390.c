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

int has_alpha(char* string) {
  int i;
  for(i=0; i<160 && string[i] != ' ' && string[i] != '\0' && string[i] != '\n'; i++) {
    if(isalpha(string[i]))
      return 1;
  }
  return 0;
}

struct commandline tokenize(char *merkkijono) {
  struct commandline cline;
  char tokens[4][80];
  char *token;
  char space[2] = " \0";
  int token_count = 0;
  int read = 0;
  if(isalpha(merkkijono[0])) {
    token = strcpy(tokens[0], strtok(merkkijono, space));
    printf("Luettu ekaan tokeniin merkkeja: %d\n", strlen(token));
    read += (strlen(token));
    token_count = 1;
    while(has_alpha(&merkkijono[read]) && token_count < 4) {
      token = strcpy(tokens[token_count], strtok(merkkijono, space));
      if(token != NULL && has_alpha(token)) {
        token_count++;
        read += strlen(token)+1;
      }
    }
    cline.correct = token_count;
    if (cline.correct > 0)
      cline.command = tokens[0][0];
    if (cline.correct > 1)
      strcpy(cline.supplement_1, tokens[1]);
    if (cline.correct > 2)
      strcpy(cline.supplement_2, tokens[2]);
    return cline;
  } else {
    cline.correct = 0;
    printf("Something went wrong in tokenizer. Seems the first letter of command line wasn't a letter.\n");
    return cline;
  }
  
  if(token_count < 1 || token_count > 3) {
    cline.correct = 0;
    printf("Something went wrong in tokenizer. Seems token count isn't in sane range (1-3).\n");
    return cline;
  }
  
  /*cline.command = (char)toupper(merkkijono[0]);
  strcpy(cline.supplement_1, tokens[1]);
  printf("%s\n", cline.supplement_1);
  fflush(stdout);
  strcpy(cline.supplement_2, tokens[2]);*/
  //cline.correct = 1;
  return cline;
}

/*char * tokens_to_string(struct commandline cmd) {
  char *returned = malloc(166);
  returned[0] = cmd.command;
  returned[1] = ' ';
  strcpy(&returned[2], cmd.supplement_1);
  char * space = strchr (&returned[2], (int)'\0');
  *space = ' ';
  strcpy(space+1, cmd.supplement_2);
  return returned;
}
*/
int main(void) {
  char merkkijono[160];
  memset(merkkijono, '\0', sizeof(merkkijono));
  printf("Tervetuloa taistelupeliin (vaiheessa)!\n> ");
  fflush(stdout);
  fgets(merkkijono, sizeof(merkkijono), stdin);
  struct commandline cline = tokenize(merkkijono);
  /*
  if(cline.correct == 1) {
    printf("cline correct!\n");
    fflush(stdout);
    char* command = tokens_to_string(cline);
    switch(merkkijono[0]) {
    case 'A':
      printf("%s\nPituus: %d\n", command, sizeof(merkkijono));
      break;
    default:
      ;
    }
      
    free(command);
  } else {
    printf("Problem with tokenizer!\n");
  }*/
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