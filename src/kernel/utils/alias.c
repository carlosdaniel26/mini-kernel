void start_interrupts()
{
    /* STI — Set Interrupt Flag */
    asm volatile("sti");
}

void stop_interrupts()
{
    /* CLI — Clear Interrupt Flag */
    asm volatile("cli");
}