#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mikael Nenonen k90390
// 2017-07-06

char *delete_comments(char *input) {
    enum state {
        NOT_IN_COMMENT,
        IN_LINE_COMMENT,
        IN_COMMENT_BLOCK
    } mystate;
    mystate = NOT_IN_COMMENT;
    char *len_counter = input;
    int input_length = 0;
    while(*len_counter) {
        len_counter++, input_length++;
    }
    char *input_copy = input;
    while(*input_copy) {
        if (*input == '/') {
            if(mystate == NOT_IN_COMMENT) {
                if (*(input+1) == '/') {
                    // line comment starts
                    input += 2;
                    char *copy = input;
                    int comment_length = 0;
                    while(*copy != '\n') {
                        copy++, comment_length++;
                    }
                    
                }
                if (*(input+1) == '*') {
                    // block comment starts
                }
            } else if(mystate == IN_LINE_COMMENT) {
                
            } else if(mystate == IN_COMMENT_BLOCK) {
                
            }
        }
        input++;
    }
    return 0;
}

int main(void) {
    printf("Hello world.\n");
    return 0;
}
