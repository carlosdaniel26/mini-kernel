#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <multiboot2.h>
#include <kernel/terminal.h>
#include <kernel/utils/alias.h>

#define PAGE_SIZE 4096        // 4 KB pages

uint64_t mem_ammount_kb;
uint8_t *mem_bitmap;
uint8_t *mem_start;
uint32_t bitmap_size;
uint8_t total_pages;

void detect_memory(struct multiboot_info_t* mb_info)
{
    if (mb_info->flags & 0x01)
	{
		mem_ammount_kb = (mb_info->mem_lower + mb_info->mem_upper);
	}
}

void print_ammount_mem_mb()
{
    printf("mem ammount kb: %u\n", mem_ammount_kb);
    printf("pages: %u\n", total_pages);
    printf("bitmap_size: %u\n", bitmap_size);
    printf("mem_start: %u\n\n", mem_start);
}

uint32_t get_page_number(void *ptr)
{
    return ((uintptr_t)ptr - (uintptr_t)mem_start) / PAGE_SIZE;
}

void pmm_init(struct multiboot_info_t* mb_info)
{
    detect_memory(mb_info);

    total_pages = mem_ammount_kb / PAGE_SIZE;
    bitmap_size = total_pages / (8);
    *mem_bitmap = (uint8_t*)0x100000; // start in 1 MB

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
        for (uint32_t j = 0; j < 8; j++)
        {
            // the page are free
            if (get_bit(mem_bitmap + i, j) == 0)
            {
                // now in use
                set_bit(mem_bitmap + i, j);
                printf("i:%u\nj:%u\n", i, j);

                return (void*)  (mem_start + (i+j) * PAGE_SIZE);
            }
            // the page are in use
            else
            {
                continue;
            }
        }
    }
}

void *pmm_free_page(void* ptr)
{
    uint32_t page_number = get_page_number(ptr);

    if ( page_number >= total_pages)
        return;

    uint32_t byte_index = page_number / 8;
    uint32_t bit_index  = page_number % 8;

    unset_bit(&mem_bitmap[byte_index], bit_index);

}

void test_pmm()
{
    uint8_t *ptr_1 = pmm_alloc_page();
    printf("ptr_1: %u\n", ptr_1);

    uint8_t *ptr_2 = pmm_alloc_page();
    printf("ptr_2: %u\n", ptr_2);

    uint8_t *ptr_3 = pmm_alloc_page();
    printf("ptr_3: %u\n", ptr_3);

    pmm_free_page(ptr_2);

    uint8_t *ptr_4 = pmm_alloc_page();
    printf("ptr_4: %u\n", ptr_4);
}