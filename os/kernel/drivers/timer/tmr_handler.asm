global tmr_handler
extern timer_handler

tmr_handler:
    pushad
    call timer_handler
    mov al, 0x20
    out 0x20, al
    popad
    iret
    