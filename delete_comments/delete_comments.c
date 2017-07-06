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
    
    while(*input) {
        if (*input == '/') {
            
        }
        input++;
    }
    return 0;
}

int main(void) {
    printf("Hello world.\n");
    return 0;
}
