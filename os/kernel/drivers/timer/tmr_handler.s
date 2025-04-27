.section .text
.global tmr_handler
.extern timer_handler
.extern sec

tmr_handler:
    pusha
    incl time
    cmpl $5, time 
    je second
    jmp finish

second:
    call sec
    movl $0, time
    jmp finish

finish:
    movb $0x20, %al
    outb %al, $0x20
    popa
    iret

.section .data
.global time
time: .long 0
