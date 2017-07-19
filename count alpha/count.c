#include <stdio.h>
#include <ctype.h>

int count_alpha(const char *str) {
	int count=0;
	while(*str) {
		if(isalpha((int)*str))
			count++;
		++str;
	}
	return count;
}
