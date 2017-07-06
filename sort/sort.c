#include <stdio.h>

void sort(int *start, int size) {
    while(1) {
        for(int i = 0; i<size; i++) {
            if(i>0) {
                if(start[i]<start[i-1]) {
                    int help = start[i];
                    start[i] = start[i-1];
                    start[i-1] = help;
                    break;
                }
            }
            if (i==size-1)
                return;
        }
    }
}

void print_array(int *start, int size) {
    for (int i=0; i<size; i++) {
        printf("%d ", start[i]);
    }
}

int main() {
    int testi[12] = {5, 6, 6, 1, 3, 1, 2, 4, 1, 1, 1, 1};
    sort(testi, 12);
    print_array(testi, 12);
    return 0;
}
