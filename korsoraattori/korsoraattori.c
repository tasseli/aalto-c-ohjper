#include <stdio.h>
#include <string.h>

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
		printf("spaces: %d", spaces_in_loop);
		spaces_in_loop = 0;
		printf("spaces: %d", spaces_in_loop);
		return 0;
	}
	int added = 0;
	if (*src == ' ') {
		spaces_in_loop++;
		if (spaces_in_loop%3 == 0 && spaces_in_loop > 0) { // niinku coming
			printf("c() Dest nyt: %s\n", dest);
			strcpy(dest, " niinku ");
			printf("c() Dest nyt: %s\n", dest);
			added += 8;
		}
		if (spaces_in_loop%4 == 0 && spaces_in_loop > 0) { // totanoin coming
			strcpy(dest, " totanoin ");
			added += 10;
		}		
	}
	return added;
}

void korsoraattori(char *dest, const char *src) {
	for(int i=0; *(dest+i) && *src; i++) {
		if (check_for_ks((dest+i), src)) {
			src += 2;
			continue;
		}
		if (check_for_ts((dest+i), src)) {
			src += 2;
			continue;
		}
		printf("k() Dest nyt: %s\n", dest);
		int added = check_if_word_needed(dest+i, src);
		i += added;
		printf("k() Dest nyt: %s\n", dest);
		*(dest+i) = *src;
		src++;
	}
	printf(dest);
}

void init_array(char *dest, int size) {
	for (int i=0; i<size; i++) {
		dest[i] = 1;
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
	return 0;
}