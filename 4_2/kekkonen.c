#include <stdio.h>
#include <string.h>

int main(void)
{
    char buffer[40];
    char *strings[] = { "Paasikivi", "Kekkonen", "Koivisto",
                        "Ahtisaari", "Halonen" };
    int left, i;

    strcpy(buffer, strings[0]);
    left = sizeof(buffer) - strlen(strings[0]);
    i = 1;
    while (left > 0 && i < 5) {
        strncat(buffer, strings[i], left - 1);
        left = left - strlen(strings[i]);
        i++;
    }
    printf("buffer: %s, length: %lu\n", buffer, strlen(buffer));
}
