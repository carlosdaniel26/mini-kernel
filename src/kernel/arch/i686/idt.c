#include <stdint.h>
#include <stdbool.h>

#include <kernel/idt.h>

#define IDTBASE    0x00000000
#define IDTSIZE    0xFF
#define IDT_ENTRIES 256

__attribute__((aligned(0x10)));    // aligned for performance
static idt_entry_struct idt[256];  // idt entries array
static idt_ptr_struct idt_ptr;

static bool vectors[IDT_ENTRIES];
extern void* isr_stub_table[];

void set_idt_desc(uint8_t vector, void* isr, uint8_t flags)
{
    idt_entry_struct* descriptor = &idt[vector];

    descriptor->base_low  = (uint32_t)isr & 0xFFFF; // Get just the first 16 bits
    descriptor->selector  = 0x08;
    descriptor->flags     = flags;
    descriptor->base_high = (uint32_t)isr >> 16;
    descriptor->always0   = 0;

}

void init_idt(void)
{
    idt_ptr.base  = (uint32_t)&idt[0];
    idt_ptr.limit = sizeof(idt_entry_struct) * IDT_ENTRIES - 1;

    for (uint8_t vector = 0; vector < 32; vector++)
    {
        set_idt_desc(vector, isr_stub_table[vector], 0x8E); // 0x8E = interrupt gate
        vectors[vector] = true;
    }

    __asm__ volatile ("lidt %0" : : "m"(idt_ptr)); // load new idt
    __asm__ volatile ("sti"); // set the interrupt flag

}