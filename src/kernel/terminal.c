#include "terminal.h"

#include "vga.h"
#include "../include/string.h"

#define VGA_WIDTH  80
#define VGA_HEIGHT 25

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint8_t terminal_background_color;
uint8_t terminal_color_scheme;
uint16_t* terminal_buffer;

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_set_background_color(VGA_COLOR_BLUE);
	terminal_setcolor(VGA_COLOR_WHITE);

	terminal_initialize_buffer();
	terminal_initialize_background();
}

void terminal_initialize_background(void)
{
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color_scheme);
		}
	}
}

void terminal_initialize_buffer(void)
{
	terminal_buffer = (uint16_t*) 0xB8000;
}

void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
	terminal_update_color_scheme();
}

void terminal_set_background_color(uint8_t background_color)
{
	terminal_background_color = background_color;
	terminal_update_color_scheme();
}

void terminal_update_color_scheme(void)
{
	terminal_color_scheme = vga_entry_color(terminal_color, terminal_background_color);
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) 
{
	terminal_putentryat(c, terminal_color_scheme, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

void terminal_breakline(void)
{
	terminal_row++;
	terminal_column = 0;
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++) 
	{
		if (data[i] == '\n')
		{
			terminal_breakline();
			i+=1;
		}

		else 
		{
			terminal_putchar(data[i]);
		}
	}
}

void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}