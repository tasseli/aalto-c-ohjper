#include <stdio.h>

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

void help(int &i) {
	i++;
	printf("++");
}

int es_copy(char *dst, const char *src) {
	int i=0;
	for (; *src != '#'; ++i) {
		*(dst+i) = *src;
		src++;
		printf("%d", i);
		printf("\n");
	}
	printf("%d", i);
	printf("\n");
	*(dst+i) = '#';
	printf(dst);
	printf("\n");
	return i;
}

char *es_token(char *s, char c) {
	return 0;
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
