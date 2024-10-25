#include <stdint.h>

uint16_t check_memory() 
{
    uint16_t memory_size;

    __asm__ volatile (
        "clc\n"                 // Clear carry flag
        "int $0x12\n"           // Call BIOS interrupt to get memory size
        : "=a"(memory_size)     // Output: AX will hold the memory size
        :                       // No input
        : "memory"              // Inform compiler that memory might be modified
    );

    return memory_size;         // Return the memory size in KB
}