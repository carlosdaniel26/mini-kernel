/* TeleTYpewriter */

#ifndef _KERNEL_TERMINAL_H
#define _KERNEL_TERMINAL_H

#include <stddef.h>

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_breakline();
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);

#endif