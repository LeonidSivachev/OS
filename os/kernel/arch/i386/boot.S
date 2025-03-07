#include "multiboot.h"

.set MULTIBOOT2_HEADER_LENGTH, header_end - header  # Длина заголовка
.set MULTIBOOT2_CHECKSUM, -(MULTIBOOT2_HEADER_MAGIC + MULTIBOOT2_ARCHITECTURE_I386 + MULTIBOOT2_HEADER_LENGTH)  # Контрольная сумма

# Multiboot2 header
.section .multiboot
.align 8 
header:
    .long MULTIBOOT2_HEADER_MAGIC         # Магическое число
    .long MULTIBOOT2_ARCHITECTURE_I386    # Архитектура
    .long MULTIBOOT2_HEADER_LENGTH        # Длина заголовка
    .long MULTIBOOT2_CHECKSUM             # Контрольная сумма

	// # VGA text mode tag (тип 4) - текстовый режим VGA
    // .short 4                              # Тип тега (4 — консоль)
    // .short 0                              # Флаги (0 — обязательный тег)
    // .long 12                              # Размер тега (12 байт)
    // .long 3                               # Флаги консоли (1 + 2: консоль 

    # End tag
    .short MULTIBOOT_TAG_TYPE_END         # Тип тега (0 — конец заголовка)
    .short 0                              # Флаги
    .long 8                               # Размер тега (8 байт)
header_end:


# Reserve a stack for the initial thread.
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp

	# Call the global constructors.
	#call _init

    pushl %ebx                # Адрес структуры multiboot_info
    pushl %eax

	# Transfer control to the main kernel.
	call kernel_main

	# Hang if kernel_main unexpectedly returns.
	cli
1:	hlt
	jmp 1b
.size _start, . - _start
