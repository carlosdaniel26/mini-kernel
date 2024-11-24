#include <stdint.h>
#include <string.h>

#include <multiboot2.h>
#include <kernel/terminal.h>

#define PAGE_SIZE 4096        // 4 KB pages

uint64_t mem_ammount_mb;
uint8_t memory_bitmap;
uint8_t total_blocks;

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