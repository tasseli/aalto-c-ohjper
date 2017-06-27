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
		*(dest+i) = *src;
		src++;
	}
	printf(dest);
}

int main() {
	char dest[180];
	for (int i=0; i<180; i++) {
		dest[i] = 1;
	}
	char src[] = "Nuorna vitsa väännettävä, ja mustan kissan paksut posket.";
	korsoraattori(dest, src);
	return 0;
}