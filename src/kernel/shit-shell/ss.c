#include <kernel/terminal.h>
#include <kernel/vga.h>
#include <kernel/utils/io.h>

#define ASCII_SPACE 32

void print_prompt()
{
	terminal_writestring("root: ");
}

void shit_shell_init()
{
	terminal_initialize_background();
	terminal_set_column(0);
	terminal_set_row(0);
}

void shit_shell_backspace()
{
	int terminal_column = terminal_get_column();

	if (terminal_column >= 6)
	{
		terminal_putentryat(' ', VGA_COLOR_WHITE, terminal_get_row()-1, terminal_get_column()-1);
		terminal_set_column(terminal_column -= 1); 
		terminal_update_cursor();
	}
}

void handler_input_shell(char key)
{
	if (key == 66)
	{
		shit_shell_backspace();
	}
	else
	{
		terminal_putchar(key);
	}
}