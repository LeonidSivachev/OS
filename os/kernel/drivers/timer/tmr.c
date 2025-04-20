#include "kernel/tmr.h"
#include "bool.h"
#include <stdio.h>

bool flag = true;

void timer_handler() {
    if (flag) {
        printf("timer");
        flag = false;
    }
}