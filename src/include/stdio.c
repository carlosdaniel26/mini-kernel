#include "../kernel/terminal.h"

int printf(const char* __restrict, ...);

int putchar(char character)
{
    terminal_write(&character, sizeof(character));

    return character;
}

int puts(const char*);