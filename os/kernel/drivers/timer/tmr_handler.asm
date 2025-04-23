global tmr_handler
extern timer_handler

tmr_handler:
    pushad
    call timer_handler
    popad
    iret