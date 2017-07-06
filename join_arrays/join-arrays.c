#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mikael Nenonen k90390
// 2017-07-06

int *join_arrays(unsigned int s1, int *a1, unsigned int s2, int *a2, unsigned int s3, int *a3) {
    int *result = (int *) malloc((s1+s2+s3)*sizeof(int));
    memcpy(result, (void *) a1, s1*sizeof(int));
    int *beginning_of_2 = &result[s1];
    memcpy(beginning_of_2, a2, s2*sizeof(int));
    int *beginning_of_3 = &result[s1+s2];
    memcpy(beginning_of_3, a3, s3*sizeof(int));
    return result;
}

int main(void)
{
    /* testing exercise. Feel free to modify */
    int a1[] = { 1, 2, 3, 4, 5 };
    int a2[] = { 10, 11, 12, 13, 14, 15, 16, 17 };
    int a3[] = { 20, 21, 22 };

    int *joined = join_arrays(5, a1, 8, a2, 3, a3);

    for (int i = 0; i < 5 + 8 + 3; i++) {
        printf("%d  ", joined[i]);
    }
    printf("\n");

    return 0;
}
