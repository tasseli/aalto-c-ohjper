#include <string.h>
#include <stdio.h>
#include "source.h"

int main()
{
    /* testing exercise. Feel free to modify */
    struct cargo c = { "Bananas", 10000, 1500 };

    struct truck t = create_truck( "Mercedes-Benz Actros", 12.0, 12.5, c );

    printf("Length of the name: %lu\n", strlen(t.name));

    // shortening the name, if it is very long
    t.name[20] = 0;

    if (t.length < 1)
	printf("Length is too short!\n");

    if (t.weight > 100)
	printf("Too heavy\n");

    printf("cargo: %s\n", t.crg.title);

    print_truck(&t);

    return 0;
}
