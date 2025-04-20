global tmr_handler
extern timer_handler

tmr_handler:
    pushad
    call tmr_handler
    popad
    iret