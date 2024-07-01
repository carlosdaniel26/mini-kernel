#include <kernel/gdt.h>

gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;

void set_gdt_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
    // set base adress
    gdt_entries[num].base_low = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high = (base >> 24) & 0xFF;

    // set the limit
    gdt_entries[num].limit_low = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    // set flags
    gdt_entries[num].granularity |= (granularity & 0xF0);
    gdt_entries[num].access = access;
}

void load_gdt() // Renamed load function to avoid conflict
{
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
    gdt_ptr.base = (uint32_t)&gdt_entries;

    // Load the gdt
    asm volatile("lgdt (%0)" : : "r"(&gdt_ptr));
    asm volatile("mov $0x10, %%ax; \
                  mov %%ax, %%ds; \
                  mov %%ax, %%es; \
                  mov %%ax, %%fs; \
                  mov %%ax, %%gs; \
                  ljmp $0x08, $next_label; \
                  next_label:": : : "eax");
  
}

void init_gdt()
{
    set_gdt_gate(0, 0, 0, 0, 0);                // Null segment
    set_gdt_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Kernel code segment
    set_gdt_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Kernel data segment
    set_gdt_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User code segment
    set_gdt_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User data segment

    load_gdt();
}