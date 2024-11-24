#include <kernel/utils/alias.h>

#include <kernel/utils/io.h>
#include <kernel/terminal.h>
#include <kernel/shit-shell/ss.h>

/*
 * The array is based on the PS/2 Scan Codes 
 *
 * https://techdocs.altium.com/display/FPGA/PS2+Keyboard+Scan+Codes
 * https://wiki.osdev.org/PS/2_Keyboard
 *
 */
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

void isr_keyboard() 
{
     stop_interrupts();

     uint8_t scancode = inb(0x60);

     handler_input_shell(scancode);

     outb(0x20, 0x20);
     start_interrupts();
}