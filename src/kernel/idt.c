#include <stdint.h>

#include "idt.h"

#define IDTBASE    0x00000000
#define IDTSIZE    0xFF
#define IDT_ENTRIES 256

void set_idt_desc(int n, uint32_t offset, uint16_t selector, uint8_t flags, idt_entry_struct* idt)
{
    idt[n].base_low = (offset & 0xFFFF);
    idt[n].base_high = (offset << 16);
    idt[n].selector = selector;
    idt[n].always0 = 0;
    idt[n].flags = flags;
    idt[n].base_high = (offset >> 16) & 0xFFFF;
}

void init_idt(idt_ptr_struct* idt_ptr, idt_entry_struct idt_entry_1)
{
    idt_ptr->limit = sizeof(struct idt_entry_struct) * IDT_ENTRIES - 1;
    idt_ptr->base  = (uint32_t)&idt_entry_1;

    load_idt((uint32_t)&idt_ptr);

}