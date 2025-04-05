#include <kernel/gdt.h>
#include <kernel/tty.h>
#include <kernel/multiboot.h>
#include <kernel/idt.h>

#include <stdio.h>
#include <stdint.h>

void kernel_main(uint32_t magic, uint32_t* multiboot_info_addr) {
    terminal_initialize();
    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        printf("incorrect_magic\n");
        abort();
    }
    init_gdt();
    init_idt();
    // parse_multiboot2_tags(multiboot_info_addr, 1 << MULTIBOOT_TAG_TYPE_MMAP);
    // volatile a = 0;
    // volatile int b = 5;
    // volatile c = b / a;
    // printf("if exception not happend!\n");
}