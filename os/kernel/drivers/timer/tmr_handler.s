.section .text
.global tmr_handler
.extern timer_handler

tmr_handler:
    pusha

    call timer_handler

    movb $0x20, %al
    outb %al, $0x20

    popa
    iret