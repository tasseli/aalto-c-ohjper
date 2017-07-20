#include <stdio.h>

int main(int argc, char *argv[]) {
	printf("This program was called with %d parameters\n", argc);
	printf("They were (including the program name itself):\n");
	for (int i = 0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}
}
