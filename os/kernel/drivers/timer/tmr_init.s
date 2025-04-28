.section .text
.global pit_init

pit_init:
    movb $0x36, %al
    outb %al, $0x43
    movw $0xFFFF, %ax
    outb %al, $0x40
    movb %ah, %al
    outb %al, $0x40
    ret
