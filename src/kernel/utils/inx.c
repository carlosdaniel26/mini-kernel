#include <stdint.h>

uint8_t inb(uint16_t port) 
{
    uint8_t ret; // return value

    // Start of inline assembly statement
    __asm__ volatile ( "inb %w1, %b0"  // Assembly instruction to read a byte from the specified port
                   : "=a"(ret)         // "=a" specifies that register 'eax' will hold the return value
                   : "Nd"(port)        // "Nd" specifies that 'port' is an I/O port number
                   : "memory");        // Informs the compiler that the instruction can access memory

    return ret;  // Returns the value read from the input/output port
}

void outb(uint16_t port, uint8_t val) 
{
    __asm__ volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}

void io_wait(void)
{
    outb(0x80, 0);
}