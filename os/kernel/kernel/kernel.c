#include <stdio.h>
#include <kernel/descriptor_tables.h>
#include <kernel/tty.h>

void kernel_main(void) {
	//init_descriptor_tables();
	terminal_initialize();
	printf("hello");
}