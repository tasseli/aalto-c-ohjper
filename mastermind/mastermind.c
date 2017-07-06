//
//  mastermind.c
//  
//
//  Created by Nenonen Mikael k90390 on 22/06/17.
//  Feat int main() courtesy of the course
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "source.h"

int in(const int guess, const int *solution, unsigned int len) {
    for(int i=0; i<len; i++) {
        if(guess == solution[i])
            return 1;
    }
    return 0;
}

void mastermind(const int *solution, const int *guess, char *result, unsigned int len) {
    for (int i = 0; i < len; i++) {
        if(guess[i] == solution[i]) {
            result[i] = '+';
        } else if(in(guess[i], solution, len)) {
            result[i] = '*';
        } else {
            result[i] = '-';
        }
    }
}

int main()
{
    /* 03-mastermind */
    int sol[6], guess[6];
    char result[7];
    srand((unsigned) time(NULL));
    for (int i = 0; i < 6; i++) {
        sol[i] = rand() % 10;
        // uncomment below, if you want to cheat (or test)
        //printf("%d ", sol[i]);
    }
    unsigned int attempts = 10;
    do {
        printf("\nAttempts remaining: %d -- give 6 numbers: ", attempts);
        for (int i = 0; i < 6; i++)
            scanf("%d", &guess[i]);
        mastermind(sol, guess, result, 6);
        result[6] = 0;
        printf("  Result: %s", result);
    } while (attempts-- && strcmp(result, "++++++"));
    
    return 0;
}
