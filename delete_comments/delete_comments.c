#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mikael Nenonen k90390
// 2017-07-06

char *delete_comments(char *input) {
    char *len_counter = input;
    int input_length = 0;
    while(*len_counter) {
        len_counter++, input_length++;
    }
    char *input_copy = input;
    while(*input_copy) {
        if (*input_copy == '/') {
            if (*(input_copy+1) == '/') {
                // line comment starts
                char *copy = input_copy;
                int comment_length = 1;
                while(*copy != '\n') {
                    copy++, comment_length++;
                }
                char *rest = copy+1;
                int rest_length = 0;
                while(*copy) {
                    rest_length++, copy++;
                }
                // move the rest of the input to replace the comment. Memmove?
                input_copy = (char *) memmove(input_copy, rest, rest_length+1);
                continue;
            }
            if (*(input_copy+1) == '*') {
                // block comment starts
                char *copy = input_copy;
                while(!(*copy == '*' && *(copy+1) == '/')) {
                    copy++;
                }
                char *rest = copy+2;
                int rest_length = 0;
                while(*copy) {
                    rest_length++, copy++;
                }
                // move the rest of the input to replace the comment. Memmove?
                input_copy = (char *) memmove(input_copy, rest, rest_length+1);
                // add one or two to compensate for the longer comment, and move as before.
            }
        }
        input_copy++;
    }
    return input;
}

/* Read given file <filename> to dynamically allocated memory.
 * Return pointer to the allocated memory with file content, or
 * NULL on errors.
 */
char *read_file(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f)
        return NULL;
    
    char *buf = NULL;
    unsigned int count = 0;
    const unsigned int ReadBlock = 100;
    unsigned int n;
    do {
        buf = realloc(buf, count + ReadBlock + 1);
        n = fread(buf + count, 1, ReadBlock, f);
        count += n;
    } while (n == ReadBlock);
    
    buf[count] = 0;
    
    return buf;
}


int main(void)
{
    char *code = read_file("testifile.c");
    if (!code) {
        printf("No code read");
        return -1;
    }
    printf("-- Original:\n");
    fputs(code, stdout);
    
    code = delete_comments(code);
    printf("-- Comments removed:\n");
    fputs(code, stdout);
    
    free(code);
    return 0;
}
