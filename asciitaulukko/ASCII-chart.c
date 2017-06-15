#include <stdio.h>
#include <ctype.h>

void ascii_chart(int min, int max) {
	int remainder = 0;
  for(int i = min ; i <= max ; i++){
		if (isprint(i))
		  printf("%3d 0x%02x %c", i, i, i);
		else
      printf("%3d 0x%02x ?", i, i);
    if (remainder % 4 != 3) {
      printf("\t");
      ++remainder;
    }
    else {
      printf("\n");
      remainder -= 3;
    }
  }
}

int main(void) {
  printf("Anna alku- ja loppukoodi ASCII-tulostusvälille välillä erotettuna.\n");
  int a = 0, b = 0;
  scanf("%d %d", &a, &b);
	ascii_chart(a, b);
	return 0;
}

