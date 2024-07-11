#include <kernel/terminal.h>
#include <kernel/vga.h>

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
	terminal_writestring("root: ");
	terminal_update_cursor();
	while(1)
	{
		
	}
}

void shit_shell_backspace()
{
	int terminal_row = terminal_get_row();

	if (terminal_row >= 6)
	{
		terminal_putentryat(' ', VGA_COLOR_WHITE, terminal_get_row()-1, terminal_get_column()-1);
		terminal_set_row(terminal_row -= 1); 
		terminal_update_cursor();
	}
}

void handler_input_shell(char key)
{
	if (key == 0)
	{
		shit_shell_backspace();
	}
	else
	{
		terminal_putchar(key);
	}
}