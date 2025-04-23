#include "kernel/tmr.h"
#include "bool.h"
#include <stdio.h>

int counter = 0;

void timer_handler() {
    ++counter;
    printf("k");
    if (counter % 36 == 0) {
        printf("timer!");
    }
}