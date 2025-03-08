#include <kernel/gdt.h>
#include <kernel/tty.h>
#include <kernel/multiboot.h>
#include <stdint.h>
#include <stdio.h>

void parse_multiboot2_tags(uint32_t* multiboot_info_addr) {
    //printf("%s%d\n","size_of_multiboot_info_adr: ", *multiboot_info_addr);
    uint8_t* tag_ptr = (uint8_t*) multiboot_info_addr + 8;

    while (((struct multiboot_tag*) tag_ptr)->type != MULTIBOOT_TAG_TYPE_END) {
        //printf("%s%d\n", "tag_type: ", ((struct multiboot_tag*) tag_ptr)->type );
        switch (((struct multiboot_tag*) tag_ptr)->type) {
            case MULTIBOOT_TAG_TYPE_CMDLINE: 
            {
                printf("%d) ", MULTIBOOT_TAG_TYPE_CMDLINE);
                printf("MULTIBOOT_TAG_TYPE_CMDLINE: %s\n", ((struct multiboot_tag_with_data*) tag_ptr)->data);
                break;
            }
            case MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME:
            {
                printf("%d) ", MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME);
                printf("MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME: %s\n", ((struct multiboot_tag_with_data*) tag_ptr)->data);
                break;
            }
            case MULTIBOOT_TAG_TYPE_MODULE:
            {
                printf("%d) ", MULTIBOOT_TAG_TYPE_MODULE);
                printf("MULTIBOOT_TAG_TYPE_MODULE: %s\n", ((struct multiboot_tag_with_data*) tag_ptr)->data);
                break;
            }
            case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO: 
            {
                printf("%d) ", MULTIBOOT_TAG_TYPE_BASIC_MEMINFO);
                struct multiboot_tag_basic_meminfo* basic_meminfo_ptr = ((struct multiboot_tag_basic_meminfo*) tag_ptr);
                printf("MULTIBOOT_TAG_TYPE_BASIC_MEMINFO: %d %d\n", basic_meminfo_ptr->mem_lower, basic_meminfo_ptr->mem_upper);
                break;
            }
            case MULTIBOOT_TAG_TYPE_BOOTDEV: // последние два некорректны
            {
                printf("%d) ", MULTIBOOT_TAG_TYPE_BOOTDEV);
                struct multiboot_tag_bootdev* type_bootdev_ptr = ((struct multiboot_tag_bootdev*) tag_ptr);
                printf("MULTIBOOT_TAG_TYPE_BOOTDEV: %d %d %d\n",type_bootdev_ptr->biosdev, type_bootdev_ptr->slice, type_bootdev_ptr->part);
                break;
            }
        }



        tag_ptr += ((struct multiboot_tag*) tag_ptr)->size; 
        if ((uintptr_t)tag_ptr % 8 != 0) {
            tag_ptr += 8 - ((uintptr_t)tag_ptr % 8);
        }

    }
}


void kernel_main(uint32_t magic, uint32_t* multiboot_info_addr) {
    terminal_initialize();
    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        printf("incorrect_magic\n");
        abort();
    }
    init_descriptor_tables();
    parse_multiboot2_tags(multiboot_info_addr);
}
