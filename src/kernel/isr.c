void exception_handler()
{
	// clear interrupts; stop cpu.
	__asm__ volatile ("cli; hlt");
}