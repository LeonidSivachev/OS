#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>
#include <stdio.h>

#include "vga.h"

static uint8_t last_seconds_number = 0;
static uint8_t first_seconds_number = 0;
static uint8_t last_minutes_number = 0;
static uint8_t first_minutes_number = 0;
static uint8_t last_hours_number = 0;
static uint8_t first_hours_number = 0;

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 23;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

void terminal_initialize(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
	create_time_field();
	printf("successful terminal initialization!\n");
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_shift() 
{
	for (size_t y = 0; y < (VGA_HEIGHT - 1); ++y) {
		for (size_t x = 0; x < VGA_WIDTH; ++x) {
			terminal_buffer[y * VGA_WIDTH + x] = terminal_buffer[(y + 1) * VGA_WIDTH + x];
		}
	}
	for (size_t x = 0; x < VGA_WIDTH; ++x) {
		terminal_buffer[(VGA_HEIGHT - 1) * (VGA_WIDTH) + x] = vga_entry(' ', terminal_color);
	}
	terminal_column = 0;
	terminal_row = VGA_HEIGHT - 1;
}

void terminal_putchar(char c)
{
	if (terminal_column >= VGA_WIDTH) {
		++terminal_row;
		terminal_column = 0;
	}
	if (c == '\n') {
		++terminal_row;
		terminal_column = 0;
	}
	if (terminal_row >= VGA_HEIGHT) {
		terminal_shift();
	}
	if (c != '\n') {
		terminal_putentryat(c, terminal_color, terminal_column++, terminal_row);
	}
}

void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}

void backspace() {
	if ((terminal_row != 0) || (terminal_column != 0)) {
		if (terminal_column == 0) {
			--terminal_row;
			terminal_column = VGA_WIDTH - 1;
		} else {
			--terminal_column;
		}
	}
	terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
}

void clear_screen() {
	for (size_t i = 0; i < VGA_HEIGHT; ++i) {
		for (size_t j = 0; j < VGA_WIDTH; ++j) {
			terminal_putentryat(' ', VGA_COLOR_WHITE, j, i);
		}
	}
	terminal_row = 0;
	terminal_column = 0;
}

static void create_time_field() {
	for (int i = 0; i <= VGA_WIDTH; ++i) {
		terminal_buffer[VGA_WIDTH * VGA_HEIGHT + i] = vga_entry('*', VGA_COLOR_WHITE);
	}
	char* time_string = "time: 00:00:00";
	for (int i = 0; i < strlen(time_string); ++i) {
		terminal_putentryat(time_string[i], terminal_color, i, VGA_HEIGHT + 1);
	}
}

void terminal_second() {
	size_t last_seconds_column = 13;
	size_t first_seconds_column = 12;
	size_t last_minutes_column = 10;
	size_t first_minutes_column = 9;
	size_t last_hours_column = 7;
	size_t first_hours_column = 6;
	if (last_seconds_number == 9) {
		last_seconds_number = 0;
		if (first_seconds_number == 5) {
			first_seconds_number = 0;
			if (last_minutes_number == 9) {
				last_minutes_number = 0;
				if (first_minutes_number == 5) {
					first_minutes_number = 0;
					if ((last_hours_number == 4) && (first_hours_number == 2)) {
						create_time_field();
					} else {
						if (last_hours_number == 9) {
							last_hours_number = 0;
							++first_hours_number;
						} else {
							++last_hours_number;
						}
					}
				} else {
					++first_minutes_number;
				}
			} else {
				++last_minutes_number;
			}
		} else {
			++first_seconds_number;
		}
	} else {
		++last_seconds_number;
	}
	terminal_putentryat((char) ('0' + last_seconds_number), terminal_color, last_seconds_column, VGA_HEIGHT + 1);
	terminal_putentryat((char) ('0' + first_seconds_number), terminal_color, first_seconds_column, VGA_HEIGHT + 1);

	terminal_putentryat((char) ('0' + last_minutes_number), terminal_color, last_minutes_column, VGA_HEIGHT + 1);
	terminal_putentryat((char) ('0' + first_minutes_number), terminal_color, first_minutes_column, VGA_HEIGHT + 1);

	terminal_putentryat((char) ('0' + last_hours_number), terminal_color, last_hours_column, VGA_HEIGHT + 1);
	terminal_putentryat((char) ('0' + first_hours_number), terminal_color, first_hours_column, VGA_HEIGHT + 1);
}
