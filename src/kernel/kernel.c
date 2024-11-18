#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <kernel/terminal.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/cpuid.h>
#include <kernel/drivers/keyboard.h>
#include <kernel/utils/io.h>
#include <kernel/shit-shell/ss.h>

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
	#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* just for i386 target BIN */
#if !defined(__i386__)
	#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

int kernel_main(void) 
{
	init_gdt();
	init_idt();
	init_irq();
	terminal_initialize();

	cpuid_get_brand();
	cpuid_print();

	shit_shell_init();

	while(1) {
		__asm__("hlt");
	}

	return 1;
	
}