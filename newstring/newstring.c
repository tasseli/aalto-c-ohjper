#include <stdio.h>
#include <stddef.h>

// Mikael Nenonen k90390
// 2017-06-27

void es_print(const char *s) {
	char copy[180];
	int i=0;
	for(i=0; *s != '#'; i++) {
		copy[i] = *s;
		s++;
	}
	copy[i] = 0;
	printf("%s", copy);
}

unsigned int es_length(const char *s) {
	int chars = 0;
	while(*s != '#') {
		chars++;
		s++;
	}
	return chars;
}

int es_copy(char *dst, const char *src) {
	int i=0;
	for (; *src != '#'; ++i) {
		*(dst+i) = *src;
		src++;
	}
	*(dst+i) = '#';
	return i;
}

char *es_token(char *s, char c) {
	while(*s != '#') {
		if (*s == c) {
			*s = '#';
			return s+1;
		}
		s++;
	}
	return NULL;
}

int main() {
	char jononi[] = "Hehee# moro";
	es_print(jononi);
	printf("\n");
	printf("%d", es_copy(jononi, "mor#"));
	printf("\n");
	es_print(jononi);
	printf("\n");
	return 0;
}
