#include <stdint.h>

#include "kernel/pic.h"
#include "kernel/keyboard_handler.h"
#include "stdio.h"

extern void outb(uint16_t port, uint8_t val);
extern uint8_t inb(uint16_t port);
extern void io_wait(void);

void keyboard_handler(void) {
    uint8_t scancode = inb(0x60);
    // if (scancode < 0x80) {  // Только нажатие (не отпускание)
    //     //char key = scancode_to_ascii(scancode);  // Ваша функция преобразования
    //     printf("keyboard_press!\n");
    // }
    printf("press\n");
    PIC_sendEOI(1);
    //printf("%d", inb(KEYBOARD_PORT));
}

int init_keyboard()
{
    // if (inb(0x64) != 0x02) {
    //     printf("keyboard_not_ready\n");
    // }
    for (int i = 0; i < 1; ++i) {
        outb(KEYBOARD_PORT, 0xF4);
        if (inb(KEYBOARD_PORT) == 0xFA) {
            printf("keyboard_successfull\n");   
            return 0;
        }
    }
    printf("keyboard_fault!\n");
    return -1;
}