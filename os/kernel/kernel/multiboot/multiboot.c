#include <kernel/multiboot.h>
#include <stdint.h>
#include <stdio.h>

void parse_multiboot2_tags(uint32_t* multiboot_info_addr, int32_t flag) {
    //printf("%s%d\n","size_of_multiboot_info_adr: ", *multiboot_info_addr);
    uint8_t* tag_ptr = (uint8_t*) multiboot_info_addr + 8;
    printf("--------------------------------------------------------------------------------");
    while (((struct multiboot_tag*) tag_ptr)->type != MULTIBOOT_TAG_TYPE_END) {
        //printf("%s%d\n", "tag_type: ", ((struct multiboot_tag*) tag_ptr)->type );
        switch (((struct multiboot_tag*) tag_ptr)->type) {
            case MULTIBOOT_TAG_TYPE_CMDLINE: 
            {
                if (!(flag & (1 << MULTIBOOT_TAG_TYPE_CMDLINE))) {
                    break;
                }
                printf("%d) ", MULTIBOOT_TAG_TYPE_CMDLINE);
                printf("MULTIBOOT_TAG_TYPE_CMDLINE: %s\n", ((struct multiboot_tag_with_data*) tag_ptr)->data);
                printf("--------------------------------------------------------------------------------");
                break;
            }
            case MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME:
            {
                if (!(flag & (1 << MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME))) {
                    break;
                }
                printf("%d) ", MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME);
                printf("MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME: %s\n", ((struct multiboot_tag_with_data*) tag_ptr)->data);
                printf("--------------------------------------------------------------------------------");
                break;
            }
            case MULTIBOOT_TAG_TYPE_MODULE:
            {
                if (!(flag & (1 << MULTIBOOT_TAG_TYPE_MODULE))) {
                    break;
                }
                printf("%d) ", MULTIBOOT_TAG_TYPE_MODULE);
                printf("MULTIBOOT_TAG_TYPE_MODULE: %s\n", ((struct multiboot_tag_with_data*) tag_ptr)->data);
                printf("--------------------------------------------------------------------------------");
                break;
            }
            case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO: 
            {
                if (!(flag & (1 << MULTIBOOT_TAG_TYPE_BASIC_MEMINFO))) {
                    break;
                }
                printf("%d) ", MULTIBOOT_TAG_TYPE_BASIC_MEMINFO);
                struct multiboot_tag_basic_meminfo* basic_meminfo_ptr = ((struct multiboot_tag_basic_meminfo*) tag_ptr);
                printf("MULTIBOOT_TAG_TYPE_BASIC_MEMINFO: %d %d\n", basic_meminfo_ptr->mem_lower, basic_meminfo_ptr->mem_upper);
                printf("--------------------------------------------------------------------------------");
                break;
            }
            case MULTIBOOT_TAG_TYPE_BOOTDEV: // последние два некорректны
            {
                if (!(flag & (1 << MULTIBOOT_TAG_TYPE_BOOTDEV))) {
                    break;
                }
                printf("%d) ", MULTIBOOT_TAG_TYPE_BOOTDEV);
                struct multiboot_tag_bootdev* type_bootdev_ptr = ((struct multiboot_tag_bootdev*) tag_ptr);
                printf("MULTIBOOT_TAG_TYPE_BOOTDEV: %d %d %d\n",type_bootdev_ptr->biosdev, type_bootdev_ptr->slice, type_bootdev_ptr->part);
                printf("--------------------------------------------------------------------------------");
                break;
            }
            case MULTIBOOT_TAG_TYPE_MMAP:
            {
                if (!(flag & (1 << MULTIBOOT_TAG_TYPE_MMAP))) {
                    break;
                }
                printf("%d) ", MULTIBOOT_TAG_TYPE_MMAP);
                struct multiboot_tag_mmap* mmap_tag_ptr = ((struct multiboot_tag_mmap*) tag_ptr);
                printf("MULTIBOOT_TAG_TYPE_MMAP: %d, %d\n", mmap_tag_ptr->entry_size, mmap_tag_ptr->entry_version);
                printf("entries:\n");

                // Вычисляем количество записей
                uint32_t entries_count = (mmap_tag_ptr->size - 16) / mmap_tag_ptr->entry_size;

                // Указатель на текущую запись
                struct multiboot_mmap_entry* entry = mmap_tag_ptr->entries;

                // Цикл по всем записям
                for (uint32_t i = 0; i < entries_count; i++) {
                    printf("  %d: addr=0x%l, len=0x%l, type=%d\n",
                        i, entry->addr, entry->len, entry->type);
                    // Смещаем указатель на следующую запись
                    entry = (struct multiboot_mmap_entry*)((uint8_t*)entry + mmap_tag_ptr->entry_size);
                }
                printf("--------------------------------------------------------------------------------");
                break;
            }
            case MULTIBOOT_TAG_TYPE_VBE: // не отображается
            {
                if (!(flag & (1 << MULTIBOOT_TAG_TYPE_VBE))) {
                    break;
                }
                printf("%d) ", MULTIBOOT_TAG_TYPE_VBE);
                struct multiboot_tag_vbe* vbe_tag_ptr = ((struct multiboot_tag_vbe*) tag_ptr);
                printf("MULTIBOOT_TAG_TYPE_VBE\n");
                printf("vbe_mode: %d", vbe_tag_ptr->vbe_mode);
                printf("--------------------------------------------------------------------------------");
                break;
            }
            case MULTIBOOT_TAG_TYPE_FRAMEBUFFER:
            {
                if (!(flag & (1 << MULTIBOOT_TAG_TYPE_FRAMEBUFFER))) {
                    break;
                }
                printf("%d) ", MULTIBOOT_TAG_TYPE_FRAMEBUFFER);
                struct multiboot_tag_framebuffer* framebuffer_tag_ptr = ((struct multiboot_tag_frambuffer*) tag_ptr);
                printf("MULTIBOOT_TAG_TYPE_FRAMEBUFFER\n");
                printf("framebuffer_addr: %d\n", framebuffer_tag_ptr->framebuffer_addr);
                printf("framebuffer_type: %d\n", framebuffer_tag_ptr->framebuffer_type);
                printf("--------------------------------------------------------------------------------");
                break;
            }
            case MULTIBOOT_TAG_TYPE_ELF_SECTIONS:
            {
                if (!(flag & (1 << MULTIBOOT_TAG_TYPE_ELF_SECTIONS))) {
                    break;
                }
                printf("%d) ", MULTIBOOT_TAG_TYPE_ELF_SECTIONS);
                struct multiboot_tag_elf_sections* framebuffer_tag_ptr = ((struct multiboot_tag_elf_sections*) tag_ptr);
                printf("MULTIBOOT_TAG_TYPE_ELF_SECTIONS\n");
                printf("--------------------------------------------------------------------------------");
                break;
            }
            case MULTIBOOT_TAG_TYPE_APM:
            {
                if (!(flag & (1 << MULTIBOOT_TAG_TYPE_APM))) {
                    break;
                }
                printf("%d) ", MULTIBOOT_TAG_TYPE_APM);
                struct multiboot_tag_apm* apm_tag_ptr = ((struct multiboot_tag_apm*) tag_ptr);
                printf("MULTIBOOT_TAG_TYPE_APM\n");
                printf("apm_version: %d\n", apm_tag_ptr->version);
                printf("--------------------------------------------------------------------------------");
                break;
            }
            case MULTIBOOT_TAG_TYPE_EFI32: // не отображается 
            {
                if (!(flag & (1 << MULTIBOOT_TAG_TYPE_EFI32))) {
                    break;
                }
                printf("%d) ", MULTIBOOT_TAG_TYPE_EFI32);
                struct multiboot_tag_efi32* efi32_tag_ptr = ((struct multiboot_efi32*) tag_ptr);
                printf("MULTIBOOT_TAG_TYPE_EFI32\n");
                printf("efi32_structure_pointer: %d\n", efi32_tag_ptr->pointer);
                printf("--------------------------------------------------------------------------------");
                break;
            }
            case MULTIBOOT_TAG_TYPE_EFI64: // не отображается 
            {
                if (!(flag & (1 << MULTIBOOT_TAG_TYPE_EFI64))) {
                    break;
                }
                printf("%d) ", MULTIBOOT_TAG_TYPE_EFI64);
                struct multiboot_tag_efi64* efi64_tag_ptr = ((struct multiboot_efi64*) tag_ptr);
                printf("MULTIBOOT_TAG_TYPE_EFI64\n");
                printf("efi32_structure_pointer: %d\n", efi64_tag_ptr->pointer);
                printf("--------------------------------------------------------------------------------");
                break;
            }
            case MULTIBOOT_TAG_TYPE_SMBIOS: // не отображается
            {
                if (!(flag & (1 << MULTIBOOT_TAG_TYPE_SMBIOS))) {
                    break;
                }
                printf("%d) ", MULTIBOOT_TAG_TYPE_SMBIOS);
                struct multiboot_tag_smbios* smbios_tag_ptr = ((struct multiboot_smbios*) tag_ptr);
                printf("MULTIBOOT_TAG_TYPE_SMBIOS\n");
                printf("--------------------------------------------------------------------------------");
                break;
            }
            case MULTIBOOT_TAG_TYPE_ACPI_OLD:
            {
                if (!(flag & (1 << MULTIBOOT_TAG_TYPE_ACPI_OLD))) {
                    break;
                }
                printf("%d) ", MULTIBOOT_TAG_TYPE_ACPI_OLD);
                struct multiboot_tag_acpi* aspi_old_tag_ptr = ((struct multiboot_tag_acpi*) tag_ptr);
                printf("MULTIBOOT_TAG_TYPE_ACPI_OLD\n");
                printf("--------------------------------------------------------------------------------");
                break;
            }
            case MULTIBOOT_TAG_TYPE_ACPI_NEW: // не отображается
            {
                if (!(flag & (1 << MULTIBOOT_TAG_TYPE_ACPI_NEW))) {
                    break;
                }
                printf("%d) ", MULTIBOOT_TAG_TYPE_ACPI_NEW);
                struct multiboot_tag_acpi* aspi_new_tag_ptr = ((struct multiboot_tag_acpi*) tag_ptr);
                printf("MULTIBOOT_TAG_TYPE_ACPI_NEW\n");
                printf("--------------------------------------------------------------------------------");
                break;
            }
            case MULTIBOOT_TAG_TYPE_NETWORK: // не отображается
            {
                if (!(flag & (1 << MULTIBOOT_TAG_TYPE_NETWORK))) {
                    break;
                }
                printf("%d) ", MULTIBOOT_TAG_TYPE_NETWORK);
                struct multiboot_tag_network*  network_tag_ptr = ((struct multiboot_tag_network*) tag_ptr);
                printf("MULTIBOOT_TAG_TYPE_ACPI_NEW\n");
                printf("--------------------------------------------------------------------------------");
                break;
            }
            case MULTIBOOT_TAG_TYPE_EFI_MMAP: // не отображается
            {
                if (!(flag & (1 << MULTIBOOT_TAG_TYPE_EFI_MMAP))) {
                    break;
                }
                printf("%d) ", MULTIBOOT_TAG_TYPE_EFI_MMAP);
                struct multiboot_tag_efi_mmap*  efi_mmap_tag_ptr = ((struct multiboot_tag_efi_mmap*) tag_ptr);
                printf("MULTIBOOT_TAG_TYPE_EFI_MMAP\n");
                printf("--------------------------------------------------------------------------------");
                break;
            }
            case MULTIBOOT_TAG_TYPE_EFI_BS: // не отображается
            {
                if (!(flag & (1 << MULTIBOOT_TAG_TYPE_EFI_BS))) {
                    break;
                }
                printf("%d) ", MULTIBOOT_TAG_TYPE_EFI_BS);
                struct multiboot_tag_efi_bs*  efi_bs_tag_ptr = ((struct multiboot_tag_efi_bs*) tag_ptr);
                printf("MULTIBOOT_TAG_TYPE_EFI_BS\n");
                printf("--------------------------------------------------------------------------------");
                break;
            }
            case MULTIBOOT_TAG_TYPE_EFI32_IH: // не отображается
            {
                if (!(flag & (1 << MULTIBOOT_TAG_TYPE_EFI32_IH))) {
                    break;
                }
                printf("%d) ", MULTIBOOT_TAG_TYPE_EFI32_IH);
                struct multiboot_tag_efi32_ih*  efi32_ih_tag_ptr = ((struct multiboot_tag_efi32_ih*) tag_ptr);
                printf("MULTIBOOT_TAG_TYPE_EFI32_IH\n");
                printf("--------------------------------------------------------------------------------");
                break;
            }
            case MULTIBOOT_TAG_TYPE_EFI64_IH: // не отображается
            {
                if (!(flag & (1 << MULTIBOOT_TAG_TYPE_EFI64_IH))) {
                    break;
                }
                printf("%d) ", MULTIBOOT_TAG_TYPE_EFI64_IH);
                struct multiboot_tag_efi64_ih*  efi64_ih_tag_ptr = ((struct multiboot_tag_efi64_ih*) tag_ptr);
                printf("MULTIBOOT_TAG_TYPE_EFI64_IH\n");
                printf("--------------------------------------------------------------------------------");
                break;
            }
            case MULTIBOOT_TAG_TYPE_LOAD_BASE_ADDR:
            {
                if (!(flag & (1 << MULTIBOOT_TAG_TYPE_LOAD_BASE_ADDR))) {
                    break;
                }
                printf("%d) ", MULTIBOOT_TAG_TYPE_LOAD_BASE_ADDR);
                struct multiboot_tag_load_base_addr*  load_base_addr_tag_ptr = ((struct multiboot_tag_load_base_addr*) tag_ptr);
                printf("MULTIBOOT_TAG_TYPE_LOAD_BASE_ADDR\n");
                printf("--------------------------------------------------------------------------------");
                break;
            }
            
            
        }
        tag_ptr += ((struct multiboot_tag*) tag_ptr)->size; 
        if ((uintptr_t)tag_ptr % 8 != 0) {
            tag_ptr += 8 - ((uintptr_t)tag_ptr % 8);
        }

    }
}