#include <stdio.h>
#include <string.h>
#include <stdarg.h>

// Mikael Nenonen k90390
// 2017-08-10

int myprint(const char *str, ...) {
  int count=0;
  int length=0;
  va_list args;
  va_start(args, str);
  int i;
  for (i=0; *(str+i) != '\0'; i++) {
    if(*(str+i) == '&') count++;
    length++;
  }
  int j;
  for(j=0; j<length; j++) {
    *(str+j) == '&' ? printf("%d", (va_arg(args, int))) : fputc((int)*(str+j), stdout) ;
  }
  va_end(args);
  return count;
}
