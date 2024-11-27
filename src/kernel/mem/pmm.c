#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <multiboot2.h>
#include <kernel/terminal/terminal.h>
#include <kernel/utils/alias.h>

#define BLOCK_SIZE 4096        // 4 KB pages

uint64_t mem_ammount_kb;
uint8_t *mem_bitmap;
uint8_t *mem_start;
uint32_t bitmap_size;
uint8_t total_blocks;

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
    printf("blocks: %u\n", total_blocks);
    printf("bitmap_size: %u\n", bitmap_size);
    printf("mem_start: %u\n\n", mem_start);
}

uint32_t get_block_number(void *ptr)
{
    return ((uintptr_t)ptr - (uintptr_t)mem_start) / BLOCK_SIZE;
}

void pmm_init(struct multiboot_info_t* mb_info)
{
    detect_memory(mb_info);

    total_blocks = mem_ammount_kb / BLOCK_SIZE;
    bitmap_size = total_blocks / (8);
    mem_bitmap = (uint8_t*)0x100000; // start in 1 MB

    memset(mem_bitmap, 0, bitmap_size); // init the bitmap

    mem_start = (uint8_t*)0x100000 + bitmap_size;
    /**
     * [1MB][BITMAP][MEM]
     */
}

void *pmm_alloc_block()
{
    for (uint32_t i = 0; i < total_blocks; i++)
    {
        // bits
        for (uint32_t j = 0; j < 8; j++)
        {
            // the block are free
            if (get_bit(mem_bitmap + i, j) == 0)
            {
                // now in use
                set_bit(mem_bitmap + i, j);
                printf("i:%u\nj:%u\n", i, j);

                return (void*)  (mem_start + (i+j) * BLOCK_SIZE);
            }
            // the block are in use
            else
            {
                continue;
            }
        }
    }
    
    return NULL;
}

void pmm_free_block(void *ptr)
{
    uint32_t block_number = get_block_number(ptr);

    if ( block_number >= total_blocks)
        return;

    uint32_t byte_index = block_number / 8;
    uint32_t bit_index  = block_number % 8;

    unset_bit(&mem_bitmap[byte_index], bit_index);

}