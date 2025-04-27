#include "kernel/keyboard_handler.h"

extern void outb(uint16_t port, uint8_t val);
extern uint8_t inb(uint16_t port);
extern void io_wait(void);

bool first_press_flag = true;

static const char kbd_us_scancode_set2[] = {
    0,   0,   '1', '2', '3', '4', '5', '6',  // 00-07
    '7', '8', '9', '0', '-', '=', '\b', '\t', // 08-0F
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',   // 10-17
    'o', 'p', '[', ']', '\n', 0,   'a', 's',  // 18-1F
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',   // 20-27
    '\'','`', 0,   '\\','z', 'x', 'c', 'v',   // 28-2F
    'b', 'n', 'm', ',', '.', '/', 0,   '*',   // 30-37
    0,   '_', 0,   0,   0,   0,   0,   0       // 38-3F
};

void keyboard_handler(void) 
{
    if (first_press_flag && finish_kernel_flag) {
        first_press_flag = false;
        clear_screen();
    }
    handle_press();
}


int init_keyboard()
{
    for (int i = 0; i < 5; ++i) {
        outb(KBRD_DATA_PORT, 0xF4);
        if (inb(KBRD_DATA_PORT) == ACK) {
            printf("keyboard_successfull\n");   
            return 0;
        }
    }
    printf("keyboard_fault!\n");
    return -1;
}

static void handle_press() 
{
    if (!(inb(KBRD_STATUS_PORT) & 0x01)) {
        PIC_sendEOI(1);
        return;
    }
    uint8_t scancode = inb(KBRD_DATA_PORT);
    if (scancode == 0xE0 || scancode == 0xF0) {
        PIC_sendEOI(1);
        return;
    }
    if (scancode == 0x66 || scancode == 0x0E) {
        backspace();
    } else if (scancode < sizeof(kbd_us_scancode_set2)) {
        char c = kbd_us_scancode_set2[scancode];
        if (c != 0) {
            putchar(c);
        }
    }

    PIC_sendEOI(1);
}