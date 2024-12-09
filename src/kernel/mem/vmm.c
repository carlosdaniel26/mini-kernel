/**
 * https://en.wikipedia.org/wiki/Control_register
 * https://youtu.be/oD1_3iL12mU?si=d3vTPy--fcKyRxD6
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <kernel/mem/pmm.h>
#include <kernel/mem/vmm.h>

#define TABLE_SIZE 1024

extern uint32_t kernel_start;
extern uint32_t kernel_end;
extern uint32_t kernel_size;

uint32_t *p4_table;
uint32_t *p3_table;

void set_cr3() 
{
    __asm__ volatile("mov %0, %%cr3" : : "r" (p4_table));
}

void set_cr0() 
{
    uint32_t cr0_value;

    __asm__ volatile("mov %%cr0, %0" : "=r" (cr0_value));

    cr0_value |= 0x80000001;

    __asm__ volatile("mov %0, %%cr0" : : "r" (cr0_value));
}

void configure_paging_directories()
{
    // give chunks for the pages
    p4_table = pmm_alloc_block();
    p3_table = pmm_alloc_block();
    memset(p4_table, 0, TABLE_SIZE * sizeof(uint32_t));
    memset(p3_table, 0, TABLE_SIZE * sizeof(uint32_t));

    printf("P4 Table Address: %u, Alignment: %u\n", (uint32_t)p4_table, (uint32_t)p4_table % 4096);
    printf("P3 Table Address: %u, Alignment: %u\n", (uint32_t)p3_table, (uint32_t)p3_table % 4096);
    
    uint32_t page_directory;
    
    /* p4[0] -> p3 */
    page_directory = (uint32_t)p3_table & 0xFFFFF000; // get the address align to 4KB
    page_directory |= 0b11; // set present and write bits

    p4_table[0] = page_directory;

}

void fill_table(struct multiboot_info_t* mb_info)
{
    uint32_t counter = 768;
    uint32_t base_address = mb_info->mmap_addr;

    while (base_address < kernel_size) 
	{
        uint32_t entry = base_address | 0b11;  // write and present bits set
    	p3_table[counter] = entry;             // fill table_768[counter] with config

        // update counter
        base_address += 4096;   // go to next physical chunk
		counter++;              // go to next entry
    }
}

void init_paging(struct multiboot_info_t* mb_info)
{
	configure_paging_directories();
	fill_table(mb_info);
	set_cr3();
    set_cr0();
    //void (*higher_half_entry)() = (void (*)())0xC0000000;
    //higher_half_entry();
}
