#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

// Mikael Nenonen k90390
// 2017-08-17 16:00 - time begun.
// Decided to use an arbitrary feeling size for names of 80.
// On the assignment hand-out lecture we were given demo code where command line size was specified as 160 characters.
// As two names are given during attack, 80 should be enough for everybody then. 

int DEBUG = 0;

#define FIGHTER struct fighter
#define ATTACK struct attack

// String handling

char *join_strs(int count, ...) {
  va_list ap;
  va_start(ap, count);
  char *next_string;
  char *so_far = NULL;
  int i;
  for(i=0; i<count; i++) {
    next_string = va_arg (ap, char*);
    if(DEBUG) printf("The string so_far is: '%s'\n", so_far);
    if(!so_far) {
      so_far = realloc(so_far, 80*sizeof(char));
      strcpy(so_far, next_string);
    } else {
      so_far = realloc(so_far, (i+1)*80*sizeof(char));
      strcat(so_far, next_string);
    }
    if(DEBUG) printf("Combined: '%s'\n", so_far);  
  }
  va_end(ap);
  return so_far;
}

int has_info(char *string) {
  int i;
  for(i=0; i<160 && string[i] != ' ' && string[i] != '\0' && string[i] != '\n'; i++) {
    if(isalpha(string[i]) || isdigit(string[i]) || string[i] == '?' || string[i] == '-')
      return 1;
  }
  return 0;
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

// FIGHTER
// struct and a linked list, accessible by *first and *last item.
// Also functions for creating, adding (to list), removing, printing, printing all, freeing all, and writing fighters.

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

void print_fighter(FIGHTER f) {
  printf("Nimi: \t\t%s\nHyökkäys: \t%s\nHP: \t\t%d\n", f.name, f.attack_style, f.hp);
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

FIGHTER *new_fighter(char *name, char *a_style, int hp) {
  FIGHTER *uus = malloc(sizeof(FIGHTER));
  if(DEBUG) printf("Made a new fighter!\n");
  strcpy(uus->name, name);
  strcpy(uus->attack_style, a_style);
  uus->hp = hp;
  uus->next = NULL;
  if(first == NULL)
    first = last = uus;
  else
    add_fighter(uus, first);
  print_fighter(*uus);
  return uus;
}

int remove_fighter(char *name){
  int success = 0;
  FIGHTER *current = first;
  FIGHTER *previous = NULL;
  while(current->next != NULL) {  // If there's one more item in linked list(, first look at this one)
    if(!strcmp(current->name, name)) {
      success = 1;
      if(previous == NULL) {  // Found match and it was the first item in list.
        first = current->next;
        free(current);
        return success;
      } else {  // Found a match
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
    if(previous == NULL) {  // Found match and it was the only item in list.
      first = current->next;
      free(current);
    } else {  // Name to be removed matched
      if(previous != NULL) previous->next = current->next;
      free(current);
    }
  }
  return success;
}

void free_all_fighters() {
  if(DEBUG) printf("Vapautetaan kaikki taistelijat.\n");
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
  if(name) {
    FIGHTER *current = first;
    while(current) {
      if(!strcmp(replace_newlines(current->name), replace_newlines(name)))
        return current;
      current = current->next;
    }
  }
  printf("Virhe: taistelijaa ei löytynyt.\n");
  return NULL;
}

int write_fighter(FIGHTER *f, FILE *file) {
  char hp[80];
  sprintf(hp, "%d",f->hp);
  char *result = join_strs(7, "  [ ", f->name, " , ", f->attack_style, " , ", hp, " ]\n");
  fprintf(file, "%s", result);
  free(result);
  return 1;
}

void write_all_fighters(FILE *file) {
  fprintf(file, "fighters:\n[\n");
  FIGHTER *current = first;
  if(current) {
    while(current->next) {
      write_fighter(current, file);
      current = current->next;
    }
    write_fighter(current, file);
  }
  fprintf(file, "]\n");
  printf("Kirjoitettu.\n");
}

void read_all_fighters(FILE *file) {
  free_all_fighters();
  int i, k=0, char_read=1;
  for(i=0; i<strlen("fighters:[")+2 && char_read != EOF; i++) {
    char_read = fgetc(file);
  }
  while(!(char_read == EOF)) {
    while(!(char_read == EOF)) { // riviä kohden
      int j;
      FIGHTER current;
      char string[80];
      for(j = 0; j<strlen("  [ ") && char_read != EOF; j++) {
        char_read = fgetc(file);
        if(char_read == ']') {
          char_read = fgetc(file);
          break;
        }
      }
      for(j = 0; char_read != ',' && char_read != EOF; j++) {
        string[j] = char_read = fgetc(file);
      }
      if(char_read == ',') {
        string[j-1] = '\0';
        string[j] = '\0';
      }
      strcpy(current.name, replace_newlines(string));
      char_read = fgetc(file);
      if(char_read == EOF)
        break;
      for(j = 0; char_read != ',' && char_read != EOF && char_read != '\n'; j++) {
        string[j] = char_read = fgetc(file);
      }
      if(char_read == ',') {
        string[j-1] = '\0';
        string[j] = '\0';
      }
      strcpy(current.attack_style, replace_newlines(string));
      for(j = 0; char_read != ']' && char_read != EOF && char_read != '\n'; j++) {
        string[j] = char_read = fgetc(file);
      }
      char_read = fgetc(file);
      if(char_read == EOF)
        break;
      if(char_read == ']') {
        string[j-1] = '\0';
        string[j] = '\0';
      }
      current.hp = strtol(string, NULL, 10);
      new_fighter(current.name, current.attack_style, current.hp);
      if(char_read == '\n')
        break;
    }
    k++;
    if(k>100000) {
      printf("Virhe: looppi rikki varmaan, 100k+ merkkiä luettu jo.\n");
      break;
    }
  }
}  // Reading fighters is the final part of the assignment I haven't implemented. I'm returning the assignment before it just to make sure.

// ATTACK
// struct and a linked list, accessible by *first_a and *last_a item.

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
  new_attack("Growl", 1);
  new_attack("Dragonblade", 1);  // I want my 1 point!
  new_attack("Shriek", 1);
  new_attack("Bite", 2);
  new_attack("Curse", 2);
  new_attack("Emasculate", 2);
  new_attack("Punch", 3);
  new_attack("Crush", 3);
  new_attack("Claw", 3);
  new_attack("Headbutt", 4);
  new_attack("Kick", 5);
  new_attack("Stomp", 8);
  new_attack("Fireblow", 9);
  new_attack("Firepunch", 10);
  new_attack("Powerthrow", 12);
  new_attack("Defenestrate", 15);
  // new_attack("Decimate", n/10);  // Planning to implement. Not high priority.
  new_attack("Deorbit", 35);
  new_attack("Decapitate", 55);
}

ATTACK *find_attack(char *name) {
  if(name) {
    ATTACK *current = first_a;
    while(current) {
      if(!strcmp(current->name, name))
        return current;
      current = current->next;
    }
  }
  return NULL;
}

int write_attack(ATTACK *a, FILE *file) {  // Unused in main-loop, so far.
  char damage[80];
  char *result = join_strs(5, "  [ ", a->name, " , ", sprintf(damage, "%d",a->damage), " ]\n");
  fprintf(file, "%s", result);
  free(result);
  return 1;
}

void write_all_attacks(FILE *file) {  // Unused in main-loop, so far.
  fprintf(file, "attacks:\n[\n");
  ATTACK *current = first_a;
  if(current) {
    while(current->next) {
      write_attack(current, file);
      current = current->next;
    }
    write_attack(current, file);
  }
  fprintf(file, "]\n");
}

void ack(char *msg) {
  printf("%s\n", msg);
  fflush(stdout);
}

int assign_attack(char *name_fighter, char *name_attack) {
  if(find_attack(name_attack)) {
    FIGHTER *current = find_fighter(name_fighter);
    if(current) {
      strcpy(current->attack_style, name_attack);
      return 1;
    }
  }
  printf("Virhe: taistelija tai hyökkäys ei täsmännyt tunnettuihin.\n");
  return 0;
}

char *describe(int hp, int damage) {
  if(damage >= hp) return "SE OLI SIINÄ!";
  else if(damage >= 0.5*hp) return "Tuo todella tuntui!";
  else if(damage >= 0.25*hp) return "Pintanaarmu.";
  return "hän ei pitänyt tästä.";
}

int attack(FIGHTER *attacker, FIGHTER *defender) {
  if(attacker == NULL || defender == NULL)
    return -1;
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

// Tokenizer

char *tok(char *str, const char *delim, int *read) {
  char *countedstr = strtok(str, delim);
  char *countedstr_cpy = countedstr;
  while(*countedstr != ' ' && *countedstr != '\0' && *countedstr != '\n') {
    (*read)++;
    countedstr++;
  }
  if(DEBUG) printf("Luettu %d merkkiä onnistuneesti (sis. aiemmat välit) %s\n", *read, countedstr_cpy);
  (*read)++;  // for the token separator. Assuming there's only one! Don't give me any excess whitespaces.
  return countedstr_cpy;
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
    printf("Virhe: komento ei ollut järkevän kokoinen. Syötä komento ja mahdolliset parametrit.\nSyötä pelkkä 'H' saadaksesi ohjeen.\n");
    return cline;
  }
  return cline;
}

// Main has the loop for command line.

int main(void) {
  add_my_attacks();
  char merkkijono[160];
  memset(merkkijono, '\0', sizeof(merkkijono));
  printf("Tervetuloa taistelupeliin!\n");
  fflush(stdout);
  struct commandline cline;
  cline.command = 'H';
  while(cline.command != 'Q') {
    printf("\nAnna komento (ABDFHLWOQ?)\n> ");
    fflush(stdout);
    fgets(merkkijono, sizeof(merkkijono), stdin);
    cline = tokenize(merkkijono);
    
    if(!(cline.correct >= 1 && cline.correct <= 3)) {
      printf("Virhe: komento ei ollut järkevän kokoinen.\nAnna komentokirjain ja 0-2 parametria välein erotettuina. Apua komennolla 'H'.\n");
      continue;
    }
    switch(cline.command) {
    case 'A':
      if(cline.correct == 3) {
        FIGHTER *fpoint;
        fpoint = new_fighter(cline.supplement_1, "Headbutt", atoi(cline.supplement_2));
        printf("Tulostetaan taistelija:\n");
        print_fighter(*fpoint);
      } else {
        printf("Virhe: komennon 'A' kanssa oltava tasan kaksi parametria: nimi ja HP:t.\nA <nimi> <HP>\n");
      }
      break;
    case 'B':
      if(cline.correct != 3 && cline.correct != 1) {
        printf("Virhe: komennon 'B' kanssa oltava tasan 0 tai 2 parametria: nimi ja vahinko.\nB\nB <nimi> <vahinko>\n");
      }
      if (cline.correct == 1) {
        printf("Tulostetaan kaikki hyökkäykset:\n");
        print_all_attacks();
      }
      if(cline.correct == 3) {
        if(assign_attack(cline.supplement_1, replace_newlines(cline.supplement_2))) {
          printf("Hyökkäystapa päivitetty.\n");
          printf("Tulostetaan taistelija:\n");
          print_fighter(*find_fighter(cline.supplement_1));
        } else
          printf("Hyökkäystavan päivitys ei onnistunut!\nTarkista taistelijan / hyökkäyksen nimi.\n");
      }
      break;
    case 'H':
    case '?':
        printf("Valitse joku seuraavista:\t(<n> = nimi)\nA <nimi> <HP>\tlisää taistelijan\nL\t\tlistaa taistelijat\nD <nimi>\tpoistaa taistelijan\nD -A\t\tpoistaa kaikki taistelijat\n");
        printf("B\t\tlistaa hyökkäystyylit\nB <n> <tyyli>\tvaihtaa taistelijalle uuden hyökkäystyylin\nF <n_1> <n_2>\ttaistelija_1 hyökkää kohteenaan taistelija_2\n");
        printf("H\t\tnäyttää (tämän) aputiedon\n?\t\tnäyttää (tämän) aputiedon\nW\t\tkirjoittaa pelaajien tilan oletustiedostoon\nW <tiedosto>\tkirjoittaa tilan annetulla nimellä\n");
        printf("O\t\tlukee oletustiedoston fighterlog.txt jos saatavilla\nO <tiedosto>\tlukee tiedoston annetulla nimellä\nQ\t\tlopettaa\n");
      break;
    case 'F':
      ;
      int damage = -1;
      if(cline.correct == 3)
        damage = attack(find_fighter(cline.supplement_1), find_fighter(replace_newlines(cline.supplement_2)));  // Returns -1 if can't find a fighter...
      if(cline.correct != 3)
        printf("Virhe: komennon F kanssa oltava tasan kaksi parametria:\nhyökkäävän ja puolustavan taistelijan nimet (kirjoitusasu tarkka).\nF <nimi_hyökkääjän> <nimi_puolustajan>\n");
      if(damage == -1)  // ... which is used here
        printf("Virhe: toista taistelijoista ei löydy! Tarkasta taistelijoiden nimien kirjoitusasu.\n");
      break;
    case 'L':
      printf("Tulostetaan taistelijat:\n");
      print_all_fighters();
      break;
    case 'D':
      if(cline.correct == 2) {  // parameter cline.supplement_1 was given
        char newlines_cleaned[80];
        strcpy(newlines_cleaned, replace_newlines(cline.supplement_1));
        strcpy(cline.supplement_1, newlines_cleaned);
        if(DEBUG) printf("Annetaan poista-parametrina: '%s'\n", cline.supplement_1);
        if(cline.supplement_1[0] == '-' && toupper(cline.supplement_1[1]) == 'A') {  // checking if sup_1 orders to delete all fighters ...
          free_all_fighters();
          printf("Poistettu kaikki taistelijat!\n");
        } else {  // ... or a single one.
          if(remove_fighter(cline.supplement_1))
            printf("Taistelijan poisto onnistui.\n");
          else
            printf("Virhe: Taistelijan poisto epäonnistui!\n");
        }
      } else
        printf("Virhe: komennon 'D' lisäksi annettava tasan yksi parametri: poistettavan nimi.\nD <nimi>\n");
      break;
    case 'W':
      if(cline.correct == 2) {
        char *filename = malloc(280*sizeof(char));
        strcpy(filename, replace_newlines(cline.supplement_1));
        FILE *writefile;
        writefile = fopen(filename, "w");
        if(writefile) write_all_fighters(writefile);
        fclose(writefile);
        free(filename);
      }
      else if(cline.correct == 1) {
        FILE *writefile;
        writefile = fopen("fighterlog.txt", "w");
        if(writefile) {
          if(DEBUG) printf("File opened\n");
          write_all_fighters(writefile);
        }
        fclose(writefile);
      } else
        printf("Virhe: komennon 'W' kanssa annettava tasan 0 (pelkkä 'W') tai 1 parametri.\nW\nW <tiedostonimi>\n");
      break;
    case 'O':
      if(cline.correct != 2 && cline.correct != 1)
        printf("Virhe: komennon 'O' kanssa annettava tasan 0 tai 1 parametria: tiedoston nimi.\nO <nimi>\n");
      if(cline.correct == 2) {
        char *filename = malloc(280*sizeof(char));
        strcpy(filename, replace_newlines(cline.supplement_1));
        FILE *readfile;
        readfile = fopen(filename, "r");
        if(readfile) {
          read_all_fighters(readfile);
          printf("Luettu taistelijatiedosto.\n");
        }
        else
          printf("Virhe: tiedoston avaaminen ei onnistunut!\n");
        fclose(readfile);
        free(filename);
      }
      else if(cline.correct == 1) {
        FILE *readfile;
        readfile = fopen("fighterlog.txt", "r");
        if(readfile) {
          read_all_fighters(readfile);
          printf("Luettu taistelijatiedosto.\n");
        }
        else
          printf("Virhe: tiedoston avaaminen ei onnistunut!\n");
        fclose(readfile);
      }
      break;
    case 'Q':
      printf("\nKiitos pelistä.\n");
      break;
    default:
      printf("Apua saat kirjoittamalla 'H'.\n");
    }
  }
  
  free_all_attacks();
  free_all_fighters();
  return 0;
}
