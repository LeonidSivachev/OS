.section .text

/* TODO: create normal exception handlers. */

#include <kernel/exceptions_asm.h>

.macro EXCEPTION_PROLOGUE
    sub $SIZE_INTERRUPT_FRAME, %esp
.endm