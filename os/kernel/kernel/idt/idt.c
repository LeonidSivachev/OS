#include <bool.h>
#include <stdio.h>

#include "kernel/idt.h"
#include "kernel/keyboard_handler.h"
#include "kernel/pic.h"

#define IDT_MAX_DESCRIPTORS 256

__attribute__((aligned(0x10))) static idt_entry_t idt[256];
static idtr_t idtr;
static bool vectors[IDT_MAX_DESCRIPTORS];
extern void* isr_stub_table[];
extern void kbrd_handler();

__attribute__((noreturn)) void exception_handler(int32_t num, int32_t error_code);
static void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);

void exception_handler(int32_t num, int32_t error_code) {
    printf("EXCEPTION %d ERROR: %d\n", num, error_code);
    __asm__ volatile ("cli; hlt");
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
    //idt_set_descriptor(0x21,(uintptr_t) keyboard_handler, 0x8E);
    idt_set_descriptor(0x21, kbrd_handler, 0x8E);
    vectors[0x21] = true;
    init_keyboard();
    __asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
    __asm__ volatile ("sti"); // set the interrupt flag
    //outb(0x60, 0x1E);
    printf("successful_IDT_inicialization!\n");
    //printf("%d\n", 0);
} 

