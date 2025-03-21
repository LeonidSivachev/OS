#include <kernel/gdt.h>
#include <kernel/tty.h>
#include <kernel/multiboot.h>

void kernel_main(uint32_t magic, uint32_t* multiboot_info_addr) {
    terminal_initialize();
    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        printf("incorrect_magic\n");
        abort();
    }
    init_descriptor_tables();
    //parse_multiboot2_tags(multiboot_info_addr);
    //printf("11111\n222222\n33333\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n");
    for (size_t i = 0; i < 20; ++i) {
        for (size_t j = 0; j < 79; ++j) {
            printf("%c", 'a' + (i % 25));
        }
        printf("\n");
    }
    // terminal_shift();
    // printf("after_shift");
    // странная проблема с выводом
}