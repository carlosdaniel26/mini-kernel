#include <stdint.h>
#include <string.h>

#include <multiboot2.h>
#include <kernel/terminal.h>

#define PAGE_SIZE 4096        // 4 KB pages

uint64_t mem_ammount_mb;
uint8_t *mem_bitmap;
uint8_t *mem_start;
uint32_t bitmap_size;
uint8_t total_pages;

void detect_memory(struct multiboot_info_t* mb_info)
{
    if (mb_info->flags & 0x01)
	{
		mem_ammount_mb = (mb_info->mem_lower + mb_info->mem_upper) / (1024);
	}
}

void print_ammount_mem_mb()
{
    char str[64];
    unsigned_to_string(mem_ammount_mb, str);
    terminal_writestring("mem ammount: ");
    terminal_writestring(str);
    terminal_writestring("\n");
}

void pmm_init()
{
    total_pages = mem_ammount_mb / PAGE_SIZE;
    bitmap_size = total_pages / 8;
}