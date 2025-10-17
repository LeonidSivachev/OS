#ifndef _EXCEPTIONS_H
#define _EXCEPTIONS_H

#include <stdint.h>

/* TODO: create structure to send registers in c handler. */

struct interrupt_state
{
    int32_t eax;
    int32_t ebx;
    int32_t ecx;
    int32_t edx;
    int32_t esp;
    int32_t ebp;
    int32_t esi;
    int32_t edi;

    int32_t cs;
    int32_t ds;
    int32_t es;
    int32_t fs;
    int32_t gs;
    int32_t ss;

    int32_t error_code;
};


#endif /* _EXCEPTIONS_H */
