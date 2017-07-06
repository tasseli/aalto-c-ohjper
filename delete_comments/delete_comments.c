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
    char *beginning = input;
    while(*input) {
        if (*input == '/') {
            if(mystate == NOT_IN_COMMENT) {
                if (*(input+1) == '/') {
                    // line comment starts
                    input += 2;
                    char *copy = input;
                    int counter = 0;
                    while(*copy != '\n') {
                        copy++, counter++;
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
