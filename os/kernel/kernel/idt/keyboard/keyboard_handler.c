#include <stdint.h>

#include "kernel/pic.h"
#include "kernel/keyboard_handler.h"

void keyboard_handler(void) {
    // uint8_t scancode = inb(0x60);
    // if (scancode < 0x80) {  // Только нажатие (не отпускание)
    //     //char key = scancode_to_ascii(scancode);  // Ваша функция преобразования
    //     printf("keyboard!\n");
    // }
    printf("keyboard\n");
    PIC_sendEOI(1);
}