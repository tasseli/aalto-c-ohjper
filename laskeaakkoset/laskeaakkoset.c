#include <stdio.h>
#include <ctype.h>

// Mikael Nenonen k90390
// 27.6.2017

int count_alpha(const char *str) {
	// Käyttäen int isalpha(int character)
	int alpha_amount = 0;
	while (*str) {
		if (isalpha(*str))
			alpha_amount++;
		str++;
	}
	return alpha_amount;
}