#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include <kernel/idt.h>
#include <kernel/terminal.h>
#include <kernel/vga.h>
#include <kernel/pic.h>
#include <kernel/drivers/keyboard.h>
#include <kernel/utils/inx.h>

#define IDT_ENTRIES 256

idt_entry_struct idt[IDT_ENTRIES];
idt_ptr_struct ptr_idt;

bool vectors[IDT_ENTRIES];

// ISR stub table definition
void (*isr_stub_table[34])() = {
    NULL
};

void set_idt_descriptor(uint8_t vector, void (*isr)(), uint8_t flags)
{
    idt_entry_struct* descriptor = &idt[vector];

    descriptor->base_low  = (uint32_t)isr & 0xFFFF; // Get just the first 16 bits
    descriptor->selector  = 0x08;
    descriptor->flags     = flags;
    descriptor->base_high = ((uint32_t)isr >> 16) & 0xFFFF;
    descriptor->always0   = 0;
}

// ************* ISR *******************
void isr_divide_by_zero() {
    terminal_setcolor(VGA_COLOR_RED);
    terminal_writestring("EXCEPTION: Divide by zero\n");
    __asm__("cli; hlt");
}

void isr_invalid_opcode() {
    terminal_setcolor(VGA_COLOR_RED);
    terminal_writestring("EXCEPTION: Invalid opcode\n");
    __asm__("cli; hlt");
}

void isr_page_fault() {
    terminal_setcolor(VGA_COLOR_RED);
    terminal_writestring("EXCEPTION: Page fault\n");
    __asm__("cli; hlt");
}

void isr_stub_divide_by_zero() {
    // Push error code and call the actual ISR
    asm volatile("push $0");
    asm volatile("jmp isr_divide_by_zero");
}

void isr_stub_invalid_opcode() {
    // Push error code and call the actual ISR
    asm volatile("push $0");
    asm volatile("jmp isr_invalid_opcode");
}

void isr_stub_page_fault() {
    // Push error code and call the actual ISR
    asm volatile("push $0");
    asm volatile("jmp isr_page_fault");
}

void init_idt(void)
{
    ptr_idt.base  = (uint32_t)&idt[0];
    ptr_idt.limit = sizeof(idt_entry_struct) * IDT_ENTRIES - 1;

    isr_stub_table[0] = isr_stub_divide_by_zero;
    isr_stub_table[6] = isr_stub_invalid_opcode;
    isr_stub_table[14] = isr_stub_page_fault;

    set_idt_descriptor(0, isr_stub_table[0], 0x8E);
    set_idt_descriptor(6, isr_stub_table[6], 0x8E);
    set_idt_descriptor(14, isr_stub_table[14], 0x8E);

    __asm__("lidt %0" : : "m"(ptr_idt));

    for (uint8_t vector = 0; vector < 32; vector++)
    {
        if (isr_stub_table[vector] != NULL) {
            set_idt_descriptor(vector, isr_stub_table[vector], 0x8E); // 0x8E = interrupt gate
            vectors[vector] = true;
        }
    }
}

void init_irq() 
{
    // PIC_remap();
    // set_idt_descriptor(33, isr_keyboard, 0x8E); // Map IRQ 1 (keyboard) to vector 33
    // outb(0x21, ~(1 << 1)); // Unmask IRQ 1 (keyboard)
    // __asm__("sti");
}
