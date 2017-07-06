/*
 ============================================================================
 Name        : laskin.c
 Author      : Mikael Nenonen - k90390
 Version     :
 Copyright   : 
 Description : Laskinfunktiot tehtävänannon 2.3 mukaan.
 ============================================================================
 */

#include <stdio.h>
#include <math.h>

void simple_multiply(int a, int b) {
	scanf("%d %d", &a, &b);
	printf("%d * %d = %d\n", a, b, a*b);
}

void simple_math(float a, char operator, float b) {
	float returnable = 0;
	int error = 0;
	if (scanf("%f %c %f", &a, &operator, &b) != 3)
		printf("ERR");
	else {
		switch(operator) {
		case '+':
			returnable = a+b;
			break;
		case '-':
			returnable = a-b;
			break;
		case '*':
			returnable = a*b;
			break;
		case '/':
			returnable = a/b;
			break;
		case '^':
			returnable = pow(a, b);
			break;
		case 'e':
		case 'E':
			returnable = a*pow(10, b);
			break;
		default:
			error = 1;
		}
		if (!error)
			printf("%3.1f", returnable);
		else
			printf("ERR");
	}
}

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0); // Hocus Pocus, my environment works
//	simple_multiply(3, 6);

	float a = 0, b = 0;
//	printf("Syötä kaksi kokonaislukua erotettuna välilyönnillä " "\n");
//	simple_multiply(a, b);

	char o = ' ';
	printf("Syötä kaksi lukua erotettuna välein ja operaattorilla [+ - * / ^ E] esim [1 + 1]\n");
	simple_math(a, o, b);

	return 0;
}
