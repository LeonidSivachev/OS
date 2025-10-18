#include <bool.h>
#include <stdio.h>
#include <stdlib.h>

#include "kernel/idt.h"
#include "kernel/keyboard_handler.h"
#include "kernel/pic.h"

#define IDT_MAX_DESCRIPTORS 256

static const char* exceptions[] = {
    [0] = "Devide_error",
    [1] = "Debug_exception",
    [2] = "NMI_interrupt",
    [3] = "Breakpoint",
    [4] = "Overflow",
    [5] = "Bound_range_exceed",
    [6] = "Invalid_opcode",
    [7] = "Devise_not_available",
    [8] = "Double_fault",
    [9] = "Copocessor_segment_overrun",
    [10] = "Invalid_TSS",
    [11] = "Segment_not_present",
    [12] = "Stack_segment_fault",
    [13] = "General_protection_fault",
    [14] = "Page_fault",
    [15] = "Intel_reserved",
    [16] = "Math_fault",
    [17] = "Aligment_check",
    [18] = "Machine_check",
    [19] = "SIMD_Floating_point_exception",
    [20] = "Virtualization_exception",
    [21] = "Control_protection_exception",
    [22] = "Intel_reserved",
    [23] = "Intel_reserved",
    [24] = "Intel_reserved",
    [25] = "Intel_reserved",
    [26] = "Intel_reserved",
    [27] = "Intel_reserved",
    [28] = "Intel_reserved",
    [29] = "Intel_reserved",
    [30] = "Intel_reserved",
    [31] = "Intel_reserved"
};

__attribute__((aligned(0x10))) static idt_entry_t idt[256];
static idtr_t idtr;
static bool vectors[IDT_MAX_DESCRIPTORS];
extern void* isr_stub_table[];
extern void kbrd_handler();
extern void tmr_handler();
extern void pit_init();

__attribute__((noreturn)) void exception_handler(int32_t num);
static void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);

void exception_handler(int32_t num) {
    printf("EXCEPTION: %s\n", exceptions[num]);
    abort();
}

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    idt_entry_t* descriptor = &idt[vector];

    descriptor->isr_low        = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs      = 0x08;
    descriptor->attributes     = flags;
    descriptor->isr_high       = (uint32_t)isr >> 16;
    descriptor->reserved       = 0;
}

void init_idt() {
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

    for (uint8_t vector = 0; vector < 32; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
        vectors[vector] = true;
    }
    
    PIC_remap(0x20, 0x28);

    IRQ_clear_mask(1);
    // idt_set_descriptor(0x21, kbrd_handler, 0x8E);
    idt_set_descriptor(0x21, isr_stub_table[0x21], 0x8E);
    vectors[0x21] = true;
    init_keyboard();

    IRQ_clear_mask(0);
    idt_set_descriptor(0x20, tmr_handler, 0x8E);
    vectors[0x20] = true;
    pit_init();

    printf("successful_IDT_inicialization!\n");
    __asm__ volatile ("lidt %0" : : "m"(idtr));
    __asm__ volatile ("sti");
}