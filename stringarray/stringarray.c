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

void switch_strs(char **arr, int j, int i) {
    char *temp = (char *)malloc((strlen(arr[j]) + 1) * sizeof(char));
    strcpy(temp, arr[j]);
    strcpy(arr[j], arr[i]);
    strcpy(arr[i], temp);
    free(temp);
}

/* Exercise c: reorder strings in <array> to lexicographical order */
void sort_string_array(char **arr)
{
    int arr_size=0;
    char** cpy=arr;
    while(*cpy) {
        arr_size++;
        cpy++;
    }
    int ordered_to, j;
    for(ordered_to=0; ordered_to<arr_size; ordered_to++) {
        for(j=ordered_to-1; j>=0; j--) {
            if(strcmp(arr[j], arr[j+1]) > 0) {
                switch_strs(arr, j, j+1);
            }
        }
    }
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
