#include "kernel/tmr.h"

int counter = 0;

void timer_handler(void) {
    ++counter;
    //printf("k");
    if (counter % 36 == 0) {
        printf("timer!");
    }
}

void sec() {
    printf("1");
}