#include <kernel/terminal/terminal.h>

void print_prompt()
{
	terminal_writestring("root: ");
}

void shit_shell_init()
{
	print_prompt();
}