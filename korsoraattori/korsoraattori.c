#include <stdio.h>
#include <string.h>

const int ALUSTETTU = 1; // stringintsekkauslogiikkani takia on tärkeää, ettei tyhjä taulukko ole täynnä nollia.

// Mikael Nenonen k90390
// 2017-06-27

int check_for_ks(char *dest, const char *src) {
	if (*src == 'k') {
		if (*(src+1) == 's') {
			*dest = 'x';
			return 1;
		}
	}
	return 0;
}

int check_for_ts(char *dest, const char *src) {
	if (*src == 't') {
		if (*(src+1) == 's') {
			*dest = 'z';
			return 1;
		}
	}
	return 0;
}

int check_if_word_needed(char *dest, const char *src) {
	static int spaces_in_loop = 0;
	if (*src == 0) {			// My magic to reset the static counter
		spaces_in_loop = 0;
		return 0;
	}
	int added = 0;
	if (*src == ' ') {
		spaces_in_loop++;
		if (spaces_in_loop%3 == 0 && spaces_in_loop > 0) { // niinku coming
			strcpy(dest, " niinku ");
			dest[8] = ALUSTETTU;
			added += 8;
		}
		if (spaces_in_loop%4 == 0 && spaces_in_loop > 0) { // totanoin coming
			if (added == 8) {
				strcpy(dest+added-1, " totanoin ");
				dest[10+added-1] = ALUSTETTU;
				added += 17;
			} else {
				strcpy(dest, " totanoin ");
				dest[10] = ALUSTETTU;
				added += 10;
			}
		}		
	}
	return added;
}

void korsoraattori(char *dest, const char *src) {
	for(int i=0; *src; i++) {
		if (check_for_ks((dest+i), src)) {
			src += 2;
			continue;
		}
		if (check_for_ts((dest+i), src)) {
			src += 2;
			continue;
		}
		int added = check_if_word_needed(dest+i, src);
		i += added;
		if (!added)
			*(dest+i) = *src;
		src++;
	}
	printf(dest);
}

void init_array(char *dest, int size) {
	for (int i=0; i<size; i++) {
		dest[i] = ALUSTETTU;
	}
}

int main() {
	char dest[180];
	init_array(dest, 180);
	char src[] = "Nuorna vitsa väännettävä, ja";
	korsoraattori(dest, src);
	printf("\n");
	init_array(dest, 180);
	check_if_word_needed((char*)"", (char*)"");
	char src2[] = "Nuorna vitsa väännettävä, ja mustan kissan paksut posket.";
	korsoraattori(dest, src2);
	init_array(dest, 180);
	check_if_word_needed((char*)"", (char*)"");
	char src3[] = "Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam non aliquam miumau haloo hehe heh moi";
	korsoraattori(dest, src3);
	return 0;
}