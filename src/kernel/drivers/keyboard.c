#include <kernel/utils/inx.h>
#include <kernel/terminal.h>

unsigned char convertScancode(unsigned char scancode) 
{
   char characterTable[] = {
    0,    0,    '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  '0',
    '-',  '=',  0,    0x09, 'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',
    'o',  'p',  '[',  ']',  0,    0,    'a',  's',  'd',  'f',  'g',  'h',
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

    return characterTable[scancode];
}


void isr_keyboard()
{
	unsigned char status = inb(0x64);
	if (status & 0x01) // check if the least significant bit (bit 0) is set, indicating data is available
	{
		unsigned char scan_code = inb(0x60); // Read the scan code from keyboard controller
		// check if it's a key pressed event (high bit not set)
		if (!(scan_code & 0x80))
		{
			// Handle the key press event
			char combined = convertScancode(scan_code);
			if (combined != '\0')
			{
				terminal_putchar(combined);
			}
		}
	}
}