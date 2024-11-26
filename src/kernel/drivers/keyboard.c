#include <kernel/utils/alias.h>

#include <kernel/utils/io.h>
#include <kernel/terminal/terminal.h>

void isr_keyboard() 
{
     stop_interrupts();

     uint8_t scancode = inb(0x60);

     terminal_handler_input(scancode);

     outb(0x20, 0x20);
     start_interrupts();
}