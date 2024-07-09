#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <kernel/terminal.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/drivers/keyboard.h>
#include <kernel/utils/io.h>

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
	#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
	#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main(void) 
{
	terminal_initialize();
	terminal_disable_cursor();
	terminal_writestring("initializing GDT...!\n");
	init_gdt();
	terminal_writestring("initializing IDT...!\n");
	init_idt();
	terminal_writestring("initializing IRQs...!\n");
	init_irq();
	terminal_writestring("Ready!\n");
}