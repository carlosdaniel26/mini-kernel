#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <stdio.h>

#include <multiboot2.h>
#include <kernel/terminal/terminal.h>
#include <kernel/arch/gdt.h>
#include <kernel/arch/idt.h>
#include <kernel/cpu/cpuid.h>
#include <kernel/cpu/pic.h>
#include <kernel/mem/pmm.h>
#include <kernel/mem/vmm.h>
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

extern uint32_t kernel_start;
extern uint32_t kernel_end;
extern uint32_t kernel_size;

int kernel_main(struct multiboot_info_t* mb_info) 
{
	init_gdt();
	init_idt();
	init_irq();
	cpuid_get_brand();

	terminal_initialize();

	cpuid_print();
	pmm_init(mb_info);

	printf("address: %u\n", &mb_info->mmap_addr);
	printf("kernel_start: %u\n", kernel_start);

	//init_paging(mb_info);

	//shit_shell_init();
	asm volatile("sti");

	while(1) {
		
	}

	return 1;
	
}