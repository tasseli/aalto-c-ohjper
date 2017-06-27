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
		spaces_in_loop = 0;
		return 0;
	}
	int added = 0;
	if (*src == ' ') {
		spaces_in_loop++;
		if (spaces_in_loop%3 == 0 && spaces_in_loop > 0) { // niinku coming
			strcpy(dest, " niinku ");
			added += 8;
		}
		if (spaces_in_loop%4 == 0 && spaces_in_loop > 0) { // totanoin coming
			if (added == 8) {
				strcpy(dest+added-1, " totanoin ");
				added += 9;
			} else {
				strcpy(dest, " totanoin ");
				added += 10;
			}
		}
	}
	return added;
}

void korsoraattori(char *dest, const char *src) {
	int i=0;
	for(; *src; i++) {
		if (check_for_ks((dest+i), src)) {
			src += 2;
			continue;
		}
		if (check_for_ts((dest+i), src)) {
			src += 2;
			continue;
		}
		int added = check_if_word_needed(dest+i, src);
		if (!added)
			*(dest+i) = *src;
		else
			i += added-1;
		src++;
	}
	dest[i] = 0;
	char print[i];
	int j=0;
	while (j<i && dest[j] != '#') {
		print[j] = dest[j];
		j++;
	}
	printf("%s", print);
	check_if_word_needed((char *)"", (char *)"");
}

int main() {
	char dest[180];
	char src[] = "yksi auto valui itsekseen ilman kuljettajaa makea alas";
	korsoraattori(dest, src);
	printf("\n");
	char dest2[180];
	char src2[] = "1 2 3 4 5 6 7 8 9 10 11 12 13 14";
	korsoraattori(dest2, src2);
	return 0;
}
