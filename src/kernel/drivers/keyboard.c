#include <kernel/utils/alias.h>

#include <kernel/utils/io.h>
#include <kernel/shit-shell/ss.h>

void isr_keyboard() 
{
     stop_interrupts();

     uint8_t scancode = inb(0x60);

     handler_input_shell(scancode);

     outb(0x20, 0x20);
     start_interrupts();
}