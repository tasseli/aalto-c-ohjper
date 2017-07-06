#include <stdio.h>
#include <string.h>

// Mikael Nenonen k90390
// 2017-06-27

int count_substr(const char *str, const char *sub) {
	int count = 0;
	while (*str) {
		int checks_out = 1;
		for (int i=0; *(sub+i); i++) {
			if (*(sub+i) != *(str+i) || (*(str+i) == 0 && *(sub+i) != 0)) // If substring doesn't match the string starting from here, or if the string already comes to an end
				checks_out = 0;
		}
		count += checks_out;
		str++;
	}
	return count;
}

int main() {
	printf("count_substr(\"one two one twotwo three\", \"two\"): %d", count_substr("one two one twotwo three", "two"));
	return 0;
}