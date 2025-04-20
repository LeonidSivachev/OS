global kbrd_handler
extern keyboard_handler 

kbrd_handler:
    pushad
    call keyboard_handler
    popad
    iret