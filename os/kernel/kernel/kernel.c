#include <kernel/gdt.h>
#include <kernel/tty.h>
#include <kernel/multiboot.h>
#include <kernel/idt.h>
#include "kernel/keyboard_handler.h"

#include <stdio.h>
#include <stdint.h>
#include <bool.h>

bool finish_kernel_flag = false;

void kernel_main(uint32_t magic, uint32_t* multiboot_info_addr) {
    terminal_initialize();
    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        printf("incorrect_magic\n");
        abort();
    }
    init_gdt();
    init_idt();
    finish_kernel_flag = true;
    while (1) {
        __asm__ volatile ("hlt");
    }
}