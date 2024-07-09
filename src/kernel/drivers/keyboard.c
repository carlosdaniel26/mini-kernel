#include <kernel/utils/io.h>
#include <kernel/terminal.h>

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

// ISR do teclado
void isr_keyboard() 
{
	terminal_writestring("ISR keyboard called\n");
   uint8_t scancode = inb(0x60);

   if (scancode < sizeof(convertScancode)) {
        unsigned char character = convertScancode[scancode];

        if (character != 0) {
            char str[2] = {character, '\0'};
            terminal_writestring(str);
        }
   }

   outb(0x20, 0x20); // Enviar End of Interrupt (EOI) ao PIC
}