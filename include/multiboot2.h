#ifndef MULTIBOOT2_H
#define MULTIBOOT2_H

#include <stdint.h>

// https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#Boot-information


struct multiboot_info_t
{
    /* Multiboot info version number */
    uint32_t flags;

    /* Available memory from BIOS */
    uint32_t mem_lower;
    uint32_t mem_upper;

    uint32_t boot_device;
    uint32_t cmdline;
    uint32_t mods_count;
    uint32_t mods_addr;
    uint32_t syms[4];
    uint32_t mmap_length;
    uint32_t mmap_addr;

} __attribute__((packed));

#endif