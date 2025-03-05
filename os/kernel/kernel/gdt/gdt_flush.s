.global gdt_flush  # Позволяет коду на C обращаться к gdt_flush()

gdt_flush:
    mov 4(%esp),%eax # eax = gdt_ptr
    lgdt (%eax)
    mov $0x10,%eax
    mov %ax,%ds
    mov %ax,%es
    mov %ax,%fs
    mov %ax,%gs
    mov %ax,%ss
    jmp $0x08,$asm_gdt_load_exit

asm_gdt_load_exit:
    ret
