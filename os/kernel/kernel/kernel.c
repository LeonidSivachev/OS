#include <stdio.h>

#include <kernel/tty.h>

void kernel_main(void) {
	terminal_initialize();
	printf("today: %d%d:%d%d:%d", 0, 5, 0, 2, 2025);
	//printf("my_birthday_is: %d%d:%d%d:%d", 0, 1, 0, 2, 2005);
	//printf("before");
	//printf("after");
	//printf("Hello, kernel World!");
}
