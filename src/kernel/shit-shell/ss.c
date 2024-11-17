#include <kernel/terminal.h>
#include <kernel/vga.h>
#include <kernel/utils/io.h>

#define ASCII_SPACE 32

static const unsigned char convertScancode[] = {
     0,    0,    '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  '0',
     '-',  '=',  0,    0x09, 'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',
     'o',  'p',  '[',  ']',  '\n', 0,    'a',  's',  'd',  'f',  'g',  'h',
     'j',  'k',  'l',  ';',  '\'', '`',  0,    '\\', 'z',  'x',  'c',  'v',
     'b',  'n',  'm',  ',',  '.',  '/',  0,    '*',  0,    ' ',  0,    0,
     0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
     0,    0,    0,    0,    0,    0,    0,    0,    0x1B, 0,    0,    0,
     0,    0,    0,    0,    0,    0,    0,    0x0E, 0x1C, 0,    0,    0,
     0,    0,    0,    0,    0,    '/',  0,    0,    0,    0,    0,    0,
     0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
     0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0,
     0,    0,    0,    0,    0,    0,    0,    0x2C
};

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

void handler_input_shell(char scancode)
{
	char key = scancode;

	if (key == 0x0E)
	{
		shit_shell_backspace();
	}
	else if (key == 0x1C)
	{
		int row = terminal_get_row();

		terminal_set_row(row+1);
		terminal_set_column(0);

		print_prompt();
	}
	else
	{
		if (scancode < sizeof(convertScancode)) 
		{
			key = convertScancode[scancode];
	
			terminal_putchar(key);
		}
	}
}