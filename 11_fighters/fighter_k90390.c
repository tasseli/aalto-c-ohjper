#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Mikael Nenonen k90390
// 2017-08-17 16:00

int DEBUG = 0;

// FIGHTER
// struct and a linked list, accessible by *first and *last item.
// Also functions for creating, adding (to list), removing (18.8. under construction), printing, printing all, and freeing all fighters.

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
  return 1;
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

int remove_fighter(char *name){
  int success = 0;
  FIGHTER *current = first;
  FIGHTER *previous = NULL;
  while(current->next != NULL) {  // If there's one more item in linked list(, first look at this one)
    if(!strcmp(current->name, name)) {  // I wonder if strcmp works like I want it to
      success = 1;
      if(previous == NULL) { first = current->next; free(current); }  // Special case, special indentation. Found match and it was the first item in list.
      else {  // Found a match
        previous->next = current->next;
        free(current);
        return success;
      }
    } else {  // Name didn't match
      previous = current;
      current = current->next;
    }
  }  // As for the last item
  if(!strcmp(current->name, name)) {  // Found a match
    success = 1;
    if(previous == NULL) { first = current->next; free(current); }  // Found match and it was the only item in list.
    else {  // Name to be removed matched
      if(previous != NULL) previous->next = current->next;
      free(current);
    }
  }
  return success;
}

void print_fighter(FIGHTER f) {
  if(DEBUG) printf("Nimi: \t\t'%s'\nHyökkäys: \t%s\nHP: \t\t%d\n", f.name, f.attack_style, f.hp);
  else printf("Nimi: \t\t%s\nHyökkäys: \t%s\nHP: \t\t%d\n", f.name, f.attack_style, f.hp);
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

// commandline
// struct and a function for printing

struct commandline{
  char command;
  char supplement_1[80];
  char supplement_2[80];
  int correct;
};

void print_commandline(struct commandline cl) {
  printf("Komento: %c\nTieto1: %s\nTieto2: %s\nOikeita: %d\n", cl.command, cl.supplement_1, cl.supplement_2, cl.correct);
}

// tokenizer and accessories

int has_info(char *string) {
  int i;
  for(i=0; i<160 && string[i] != ' ' && string[i] != '\0' && string[i] != '\n'; i++) {
    if(isalpha(string[i]) || isdigit(string[i]) || string[i] == '?')
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
  if(DEBUG) printf("Luettu %d merkkiä onnistuneesti (sis. aiemmat välit) %s\n", *read, countedstr_cpy);
  (*read)++;  // for the token separator. Assuming there's only one.
  return countedstr_cpy;
}

char *replace_newlines(char *string) {
  char *copy = string;
  while(*string) {
    if(*string == '\n')
      *string = '\0';
    string++;
  }
  return copy;
}

struct commandline tokenize(char *merkkijono) {
  struct commandline cline;
  char tokens[4][80];
  char *token;
  char space[2] = " \0";
  int token_count = 0;
  int read = 0;
  if(isalpha(merkkijono[0]) || merkkijono[0] == '?') {
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
    printf("Virhe: ensimmäinen merkki tuskin kelpasi komennoksi.\n");
    return cline;
  }
  
  if(token_count < 1 || token_count > 3) {
    cline.correct = 0;
    printf("Virhe: komento ei ollut järkevän kokoinen (1-3 osaa).\n");
    return cline;
  }
  
  cline.command = (char)toupper(merkkijono[0]);
  strcpy(cline.supplement_1, tokens[1]);
  strcpy(cline.supplement_2, tokens[2]);
  cline.correct = 1;
  return cline;
}

// Main has the loop for command line.

int main(void) {
  char merkkijono[160];
  memset(merkkijono, '\0', sizeof(merkkijono));
  printf("Tervetuloa taistelupeliin (vaiheessa)!\n");
  fflush(stdout);
  struct commandline cline;
  cline.command = 'H';
  while(cline.command != 'Q') {
    printf("\nAnna komento (AHLDQ?)\n> ");
    fflush(stdout);
    fgets(merkkijono, sizeof(merkkijono), stdin);
    cline = tokenize(merkkijono);
    
    if(cline.correct >= 1 && cline.correct <= 3) {
      switch(cline.command) {
      case 'A':
        if(cline.correct == 3) {
          FIGHTER *fpoint;
          fpoint = new_fighter(cline.supplement_1, "Headbutt", atoi(cline.supplement_2));
          printf("Tulostetaan taistelija:\n");
          print_fighter(*fpoint);
        } else {
          printf("(A)dding tarvitsee kolme osaa; komennon A, nimen, ja HP:t.\n");
        }
        break;
      case 'H':
      case '?':
          printf("Valitse joku seuraavista:\nA <nimi> <HP>\tlisää taistelijan\n");
          printf("L\t\tlistaa taistelijat\nD <nimi>\tpoistaa taistelijan\nQ\t\tlopettaa\nH\t\tnäyttää (tämän) aputiedon\n?\t\tnäyttää (tämän) aputiedon\n");
        break;
      case 'L':
        printf("Tulostetaan taistelijat:\n");
        print_all_fighters();
        break;
      case 'D':
        if(DEBUG) printf("Giving as remove parameter: '%s'\n", replace_newlines(cline.supplement_1));
        if(remove_fighter(cline.supplement_1))
          printf("Taistelijan poisto onnistui.\n");
        else
          printf("Virhe: Taistelijan poisto epäonnistui!\n");
        break;
      case 'Q':
        printf("\nKiitos pelistä.\n");
        break;
      default:
        ;
      }
    } else {
      printf("Virhe: komento ei ollut järkevän kokoinen (1-3 osaa).\n");
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
 
