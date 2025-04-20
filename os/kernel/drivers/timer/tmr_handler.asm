global kbrd_handler
extern tmr_handler

kbrd_handler:
    pushad
    call tmr_handler
    popad
    iret