#pragma once

#define KBRD_DATA_PORT 0x60
#define KBRD_STATUS_PORT 0x64

#define ACK 0xfa
#define RESEND 0xfe

void keyboard_handler(void);
int init_keyboard();
