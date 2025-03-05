#include <kernel/gdt.h>
#include <kernel/tty.h>

void kernel_main(void) {
	terminal_initialize();
	init_descriptor_tables();
}