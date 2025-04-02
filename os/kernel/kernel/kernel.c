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
    //parse_multiboot2_tags(multiboot_info_addr, 1 << MULTIBOOT_TAG_TYPE_MMAP);
    init_gdt();
    init_idt();
    //printf("%d %d %d jfklajdsflkasj %l", 123, 456, -789, 0x1000000000);c
    parse_multiboot2_tags(multiboot_info_addr, 1 << MULTIBOOT_TAG_TYPE_MMAP);
}