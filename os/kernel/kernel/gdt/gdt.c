#include <stdint.h>
#include <stdio.h>
#include "kernel/gdt.h"

// Предоставляет нам доступ к нашим ассемблерным функциям из нашего кода на C.
extern void gdt_flush(uint32_t);

// Прототипы внешних функций.
static void init_gdt();
static void gdt_set_gate(int32_t,uint32_t,uint32_t,uint8_t,uint8_t);

gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;

// инициализирует GDT
void init_descriptor_tables()
{
   // Initialise the global descriptor table.
   init_gdt();
   printf("successful GDT initialization!\n");
}

static void init_gdt()
{
   gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
   gdt_ptr.base  = (uint32_t)&gdt_entries;
   /*
   1) num номер десктриптора
   2) base начальный адрес сегмента в виртуальной или физической памяти
   3) limit размер сегмента
   4) access байт доступа
   5) gran определяет единицы измерения
   */
   gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
   gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
   gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
   gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
   gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

   gdt_flush((uint32_t)&gdt_ptr);
}

// Устанавливает значения для одной записи в GDT.
static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
   gdt_entries[num].base_low    = (base & 0xFFFF);
   gdt_entries[num].base_middle = (base >> 16) & 0xFF;
   gdt_entries[num].base_high   = (base >> 24) & 0xFF;

   gdt_entries[num].limit_low   = (limit & 0xFFFF);
   gdt_entries[num].granularity = (limit >> 16) & 0x0F;

   gdt_entries[num].granularity |= gran & 0xF0;
   gdt_entries[num].access      = access;
} 