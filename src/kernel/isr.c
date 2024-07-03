__attribute__((noreturn))
void exception_handler()
{
	// Completely hangs the computer
	__asm__ volatile ("cli; hlt");
}