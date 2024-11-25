#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <stdio.h>

#include <multiboot2.h>
#include <kernel/terminal/terminal.h>
#include <kernel/arch/gdt.h>
#include <kernel/arch/idt.h>
#include <kernel/cpu/cpuid.h>
#include <kernel/mem/pmm.h>
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

int kernel_main(struct multiboot_info_t* mb_info) 
{
	init_gdt();
	init_idt();
	init_irq();
	cpuid_get_brand();

	terminal_initialize();

	cpuid_print();
	pmm_init(mb_info);
	print_ammount_mem_mb();
	test_pmm();

	//shit_shell_init();

	while(1) {
		__asm__("hlt");
	}

	return 1;
	
}