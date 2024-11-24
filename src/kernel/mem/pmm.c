#include <stdint.h>
#include <string.h>

#include <multiboot2.h>
#include <kernel/terminal.h>
#include <kernel/utils/alias.h>

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
    bitmap_size = total_pages / (8);
    *mem_bitmap = 0x100000; // start in 1 MB

    memset(mem_bitmap, 0, bitmap_size); // init the bitmap

    mem_start = (uint8_t*)0x100000 + bitmap_size;
    /**
     * [1MB][BITMAP][MEM]
     */
}

void *pmm_alloc_page()
{
    for (uint32_t i = 0; i < total_pages; i++)
    {
        // bits
        for (uint32_t j = 1; j < 8; j++)
        {
            // the page are free
            if (get_bit(mem_bitmap + i,j) == 0)
            {
                // now in use
                set_bit(mem_bitmap + i, j);
                
                return (void*)(mem_start + i * PAGE_SIZE);
            }
            // the page are in use
            else
            {
                continue;
            }
        }
    }
}