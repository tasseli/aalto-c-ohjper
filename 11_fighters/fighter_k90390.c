#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Mikael Nenonen k90390
// 2017-08-17 16:00

int DEBUG = 0;

#define FIGHTER struct fighter
#define ATTACK struct attack

// FIGHTER
// struct and a linked list, accessible by *first and *last item.
// Also functions for creating, adding (to list), removing (18.8. under construction), printing, printing all, and freeing all fighters.

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
  first = last = NULL;
}

FIGHTER *find_fighter(char *name) {
  FIGHTER *current = first;
  while(current) {
    if(!strcmp(current->name, name))
      return current;
    current = current->next;
  }
  return NULL;
}

char *jstr(char *str1, char *str2) {
  
}

int write_fighter(FIGHTER *f, FILE *file) {
  char hp[80];
  char *info = strcat(f->name, strcat(f->attack_style, itoa(f->hp, hp, 10)));
  printf("I'd write: '%s'\n", info);
  return 1;
}

// ATTACK
// struct and a linked list, accessible by *first and *last item.

struct attack{
  char name[80];
  int damage;
  ATTACK *next;
};

ATTACK *first_a = NULL;
ATTACK *last_a = NULL;

int add_attack(ATTACK *added, ATTACK *member) {
  while(member->next != NULL && member != last_a) {
    member = member->next;
  }
  member->next = added;
  last_a = added;
  return 1;
}

ATTACK *new_attack(char *name, int damage) {
  ATTACK *uus = malloc(sizeof(ATTACK));
  strcpy(uus->name, name);
  uus->damage = damage;
  uus->next = NULL;
  if(first_a == NULL)
    first_a = last_a = uus;
  else
    add_attack(uus, first_a);
  return uus;
}

int remove_attack(char *name){
  int success = 0;
  ATTACK *current = first_a;
  ATTACK *previous = NULL;
  while(current->next != NULL) {  // If there's one more item in linked list(, first look at this one)
    if(!strcmp(current->name, name)) {
      success = 1;
      if(previous == NULL) { first_a = current->next; free(current); }  // Special case, special indentation. Found match and it was the first item in list.
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
    if(previous == NULL) { first_a = current->next; free(current); }  // Found match and it was the only item in list.
    else {  // Name to be removed matched
      if(previous != NULL) previous->next = current->next;
      free(current);
    }
  }
  return success;
}

void print_attack(ATTACK a) {
  printf("Hyökkäys: \t%s\nVahinko: \t%d\n", a.name, a.damage);
}

void print_all_attacks() {
  ATTACK *current = first_a;
  if(current) {
    while(current->next) {
      print_attack(*current);
      current = current->next;
    }
    print_attack(*current);
  }
}

void free_all_attacks() {
  ATTACK *current = first_a;
  ATTACK *freed;
  if(current) {
    while(current->next) {
      freed = current;
      current = current->next;
      free(freed);
    }
    free(current);
  }
  first_a = last_a = NULL;
}

void add_my_attacks() {
  ATTACK *apoint;
  apoint = new_attack("Growl", 1);
  apoint = new_attack("Dragonblade", 1);  // I want my 1 point!
  apoint = new_attack("Shriek", 1);
  apoint = new_attack("Bite", 2);
  apoint = new_attack("Curse", 2);
  apoint = new_attack("Emasculate", 2);
  apoint = new_attack("Punch", 3);
  apoint = new_attack("Crush", 3);
  apoint = new_attack("Headbutt", 4);
  apoint = new_attack("Kick", 5);
  apoint = new_attack("Stomp", 8);
  apoint = new_attack("Firepunch", 10);
  apoint = new_attack("Powerthrow", 12);
  apoint = new_attack("Defenestrate", 15);
  //apoint = new_attack("Decimate", n/10);
  apoint = new_attack("Deorbit", 35);
  apoint = new_attack("Decapitate", 55);
}

ATTACK *find_attack(char *name) {
  ATTACK *current = first_a;
  while(current) {
    if(!strcmp(current->name, name))
      return current;
    current = current->next;
  }
  return NULL;
}

int assign_attack(char *name_fighter, char *name_attack) {
  if(find_attack(name_attack)) {
    FIGHTER *current = find_fighter(name_fighter);
    strcpy(current->attack_style, name_attack);
    return 1;
  }
  return 0;
}

char *describe(int hp, int damage) {
  if(damage >= hp) return "SE OLI SIINÄ!";
  else if(damage >= 0.5*hp) return "Tuo todella tuntui!";
  else if(damage >= 0.25*hp) return "Pintanaarmu.";
  return "hän ei pitänyt tästä.";
}

int attack(FIGHTER *attacker, FIGHTER *defender) {
  printf("%s on vuosien saatossa hionut huippuunsa salatun taitonsa: %s.\n", attacker->name, attacker->attack_style);
  printf("Hän hyökkää, kohteenaan %s!\n", defender->name);
  int damage = find_attack(attacker->attack_style)->damage;
  printf("Isku aiheuttaa vahinkoa %d HP!\n", damage);
  printf("%s HP: %d", defender->name, defender->hp);
  char *luonnehdinta = describe(defender->hp, damage);
  defender->hp -= damage;
  printf(" -> %d - %s\n", defender->hp, luonnehdinta);
  return find_attack(attacker->attack_style)->damage;
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
    if(isalpha(string[i]) || isdigit(string[i]) || string[i] == '?' || string[i] == '-')
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
  add_my_attacks();
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
      case 'B':
        if(cline.correct == 3) {
          if(assign_attack(cline.supplement_1, replace_newlines(cline.supplement_2))) {
            printf("Hyökkäystapa päivitetty.\n");
            printf("Tulostetaan taistelija:\n");
            print_fighter(*find_fighter(cline.supplement_1));
          } else
            printf("Hyökkäystavan päivitys ei onnistunut!\nTarkista taistelijan / hyökkäyksen nimi.\n");
        } else if (cline.correct == 1) {
          printf("Tulostetaan kaikki hyökkäykset:\n");
          print_all_attacks();
        }
        else {
          printf("(B) tarvitsee tasan yhden tai kolme osaa; komennon B, nimen, ja damagen.\n");
        }
        break;
      case 'H':
      case '?':
          printf("Valitse joku seuraavista:\nA <nimi> <HP>\tlisää taistelijan\nL\t\tlistaa taistelijat\n");
          printf("D <nimi>\tpoistaa taistelijan\nD -A\t\tpoistaa kaikki taistelijat\nH\t\tnäyttää (tämän) aputiedon\n?\t\tnäyttää (tämän) aputiedon\nQ\t\tlopettaa\n");
        break;
      case 'F':
        if(cline.correct == 3) {
          attack(find_fighter(cline.supplement_1), find_fighter(replace_newlines(cline.supplement_2)));
        }
        break;
      case 'L':
        printf("Tulostetaan taistelijat:\n");
        print_all_fighters();
        break;
      case 'D':
        strcpy(cline.supplement_1, replace_newlines(cline.supplement_1));
        if(DEBUG) printf("Annetaan poista-parametrina: '%s'\n", cline.supplement_1);
        if(cline.supplement_1[0] == '-' && toupper(cline.supplement_1[1]) == 'A') {
          free_all_fighters();
          printf("Poistettu kaikki taistelijat!\n");
        } else {
          if(remove_fighter(cline.supplement_1))
            printf("Taistelijan poisto onnistui.\n");
          else
            printf("Virhe: Taistelijan poisto epäonnistui!\n");
        }
        break;
      case 'W':
        if(cline.correct == 2)
          write_fighter(find_fighter(replace_newlines(cline.supplement_1)), stdout);
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
  
  free_all_attacks();
  free_all_fighters();
  return 0;
}
