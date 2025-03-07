#include <kernel/gdt.h>
#include <kernel/tty.h>
#include <stdint.h>
#include <stdio.h>

#define MULTIBOOT2_MAGIC_NUMBER 0x36d76289

struct tag {
    uint32_t type;
    uint32_t size;
};

struct tag_with_data {
    uint32_t type;
    uint32_t size;
    uint8_t data[];
};

void parse_multiboot2_tags(uint32_t* multiboot_info_addr) {
    //printf("%s%d\n","size_of_multiboot_info_adr: ", *multiboot_info_addr);
    uint8_t* tag_ptr = (uint8_t*) multiboot_info_addr + 8;

    while (((struct tag*) tag_ptr)->type != 0) {
        //printf("%s%d\n", "tag_type: ", ((struct tag*) tag_ptr)->type );
        if (((struct tag*) tag_ptr)->type == 2) {
            printf("%s\n", ((struct tag_with_data*) tag_ptr)->data);
        }

        tag_ptr += ((struct tag*) tag_ptr)->size; 
        if ((uintptr_t)tag_ptr % 8 != 0) {
            tag_ptr += 8 - ((uintptr_t)tag_ptr % 8);
        }

    }
}


void kernel_main(uint32_t magic, uint32_t* multiboot_info_addr) {
	terminal_initialize();
	if (magic != MULTIBOOT2_MAGIC_NUMBER) {
        printf("incorrect_magic\n");
        abort();
    }
	init_descriptor_tables();
    parse_multiboot2_tags(multiboot_info_addr);
}