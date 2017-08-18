#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Mikael Nenonen k90390
// 2017-08-17 16:00

int DEBUG = 0;

#define FIGHTER struct fighter
struct fighter{
  char name[80];
  char attack_style[32];
  int hp;
  FIGHTER *next;
};

FIGHTER *first = NULL;
FIGHTER *last = NULL;

int add_fighter(FIGHTER *added, FIGHTER *member) {
  while(member->next != NULL && member != last) {
    member = member->next;
  }
  member->next = added;
  last = added;
}

int remove_fighter(char *name){
  int success = 0;
  FIGHTER *current = first;
  FIGHTER *previous = NULL;
  while(current->next != NULL) {
    if(!strcmp(current->name, name)) { // I wonder if strcmp works like I want it to
      success = 1;
      if(previous == NULL) { first = current->next; free(current); } // Special case, special indentation. Name to be removed matched
      else { // Name to be removed matched
        previous->next = current->next;
        free(current);
      }
    } else { // Name didn't match
      current = current->next;
    }
  }
  if(!strcmp(current->name, name)) { // One last time
    success = 1;
    if(previous == NULL) { first = current->next; free(current); } // Special case, special indentation. Name to be removed matched
    else { // Name to be removed matched
      previous->next = current->next;
      free(current);
    }
  }
  return success;
}

FIGHTER *new_fighter(char *name, char *a_style, int hp) {
  FIGHTER *uus = malloc(sizeof(FIGHTER));
  strcpy(uus->name, name);
  strcpy(uus->attack_style, a_style);
  uus->hp = hp;
  uus->next = NULL;
  if(first == NULL)
    first = last = uus;
  else
    add_fighter(uus, first);
  return uus;
}

void print_fighter(FIGHTER f) {
  printf("Printing fighter\nName: \t\t%s\nAttack style: \t%s\nHP: \t\t%d\n", f.name, f.attack_style, f.hp);
}

void print_all_fighters() {
  FIGHTER *current = first;
  if(current) {
    while(current->next) {
      print_fighter(*current);
      current = current->next;
    }
    print_fighter(*current);
  }
}

void free_all_fighters() {
  FIGHTER *current = first;
  FIGHTER *freed;
  if(current) {
    while(current->next) {
      freed = current;
      current = current->next;
      free(freed);
    }
    free(current);
  }
}

struct commandline{
  char command;
  char supplement_1[80];
  char supplement_2[80];
  int correct;
};

void print_commandline(struct commandline cl) {
  printf("Command: %c\nSup1: %s\nSup2: %s\nCorrect: %d\n", cl.command, cl.supplement_1, cl.supplement_2, cl.correct);
}

int has_info(char* string) {
  int i;
  for(i=0; i<160 && string[i] != ' ' && string[i] != '\0' && string[i] != '\n'; i++) {
    if(isalpha(string[i]) || isdigit(string[i]))
      return 1;
  }
  return 0;
}

char *tok(char *str, const char *delim, int *read) {
  char *countedstr = strtok(str, delim);
  char *countedstr_cpy = countedstr;
  while(*countedstr != ' ' && *countedstr != '\0' && *countedstr != '\n') {
    (*read)++;
    countedstr++;
  }
  if(DEBUG) printf("Tokenized %d chars so far (including spaces earlier); %s\n", *read, countedstr_cpy);
  (*read)++; // for the token separator. Assuming there's only one.
  return countedstr_cpy;
}

struct commandline tokenize(char *merkkijono) {
  struct commandline cline;
  char tokens[4][80];
  char *token;
  char space[2] = " \0";
  int token_count = 0;
  int read = 0;
  if(isalpha(merkkijono[0])) {
    token = strcpy(tokens[0], tok(merkkijono, space, &read));
    token_count = 1;
    while(has_info(&(merkkijono[read])) && token_count < 4) {
      token = strcpy(tokens[token_count], tok(NULL, space, &read));
      if(token != NULL && has_info(token)) {
        token_count++;
      }
    }
    cline.correct = token_count;
    if (cline.correct > 0)
      cline.command = toupper(tokens[0][0]);
    if (cline.correct > 1) {
      strcpy(cline.supplement_1, tokens[1]);
    }
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
  
  cline.command = (char)toupper(merkkijono[0]);
  strcpy(cline.supplement_1, tokens[1]);
  strcpy(cline.supplement_2, tokens[2]);
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
  memset(merkkijono, '\0', sizeof(merkkijono));
  printf("Tervetuloa taistelupeliin (vaiheessa)!\n");
  fflush(stdout);
  struct commandline cline;
  cline.command = 'H';
  while(cline.command != 'Q') {
    printf("\nAnna komento\n> ");
    fflush(stdout);
    fgets(merkkijono, sizeof(merkkijono), stdin);
    cline = tokenize(merkkijono);
    
    if(cline.correct >= 1 && cline.correct <= 3) {
      //char* command = tokens_to_string(cline);
      switch(cline.command) {
      case 'A':
        if(DEBUG) print_commandline(cline);
        FIGHTER *fpoint;
        if(DEBUG) printf("atoi result: %d\n", atoi(cline.supplement_2));
        fflush(stdout);
        fpoint = new_fighter(cline.supplement_1, "Headbutt", atoi(cline.supplement_2));
        if(DEBUG) printf("Figher created!\n\n");
        fflush(stdout);
        print_fighter(*fpoint);
        break;
      case 'H':
        printf("Valitse joku seuraavista:\nA <nimi> <HP>\tlisää taistelijan\nQ\t\tlopettaa\n");
        break;
      case 'L':
        print_all_fighters();
        break;
      case 'D':
        if(remove_fighter(cline.supplement_1))
          printf("Remove seems to have succeeded!\n");
        else
          printf("Remove didn't succeed!\n");
        break;
      case 'Q':
        printf("\nKiitos pelistä.\n");
        break;
      default:
        ;
      }
      //free(command);
    } else {
      printf("Problem with tokenizer!\n");
    }
  }
  free_all_fighters();
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
 