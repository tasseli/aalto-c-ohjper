#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringarray.h"

// Mikael Nenonen k90390
// 2017-07-20

/* Exercise a: Initializes the string array to contain the initial
 * NULL pointer, but nothing else.
 * Returns: pointer to the array of strings that has one element
 *      (that contains NULL)
 */
char **init_string_array(void)
{
    char **empty = malloc(sizeof(char*));
    *empty = 0;
    return empty;
}

/* Releases the memory used by the strings.
 */
void release_string_array(char **arr)
{
    char** cpy = arr;
    while(*cpy) {
        free(*cpy);
        cpy++;
    }
    free(arr);
}

/* Exercise b: Add <string> to the end of array <array>.
 * Returns: pointer to the array after the string has been added.
 */
char **insert_string(char **arr, const char *str)
{
    char** cpy = arr;
    int arr_size=1;
    while(*cpy) {
        arr_size++;
        cpy++;
    }
    arr = realloc(arr, (arr_size+1)*sizeof(char*));

    const char* stringcpy = str;
    int stringlength = 0;
    while(*stringcpy) {
        stringlength++;
        stringcpy++;
    }
    arr[arr_size-1] = malloc((stringlength+1)*sizeof(char));
    
    strcpy(arr[arr_size-1], str);
    arr[arr_size] = 0;
    print_string_array(arr);
    return arr;
}


/* Exercise c: reorder strings in <array> to lexicographical order */
void sort_string_array(char **arr)
{
}

/* You can use this function to check what your array looks like.
 */
void print_string_array(char **arr)
{
    if (!arr)
        return;
    while (*arr) {
        printf("%s  ", *arr);
        arr++;
    }
    printf("\n");
}
