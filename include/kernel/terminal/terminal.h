/* TeleTYpewriter */

#ifndef _KERNEL_TERMINAL_H
#define _KERNEL_TERMINAL_H

#include <stddef.h>
#include <stdint.h>

void terminal_initialize(void);
void terminal_set_column(int index);
void terminal_set_row(int index);
int terminal_get_column();
int terminal_get_row();
void terminal_initialize_background(void);
void terminal_initialize_buffer(void);
void terminal_setcolor(uint8_t color);
void terminal_set_background_color(uint8_t background_color);
void terminal_update_color_scheme();
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void terminal_putchar(char c);
void terminal_breakline();
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void terminal_disable_cursor();
void terminal_enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void terminal_update_cursor();

#endif