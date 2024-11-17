void start_interrupts()
{
    /* STI — Set Interrupt Flag */
    __asm__("sti");
}

void stop_interrupts()
{
    /* CLI — Clear Interrupt Flag */
    __asm__("cli");
}