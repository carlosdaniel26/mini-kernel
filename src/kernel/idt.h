#ifndef IDT_H
#define IDT_H

#include <stdint.h>

typedef struct idt_entry_struct {
    uint16_t base_low;
    uint16_t selector;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_high;
}__attribute__((packed)) idt_entry_struct;

typedef struct idt_ptr_struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_ptr_struct;

void init_idt(idt_ptr_struct* idt_ptr, idt_entry_struct idt_entry_1);
void set_idt_desc(int n, uint32_t offset, uint16_t selector, uint8_t flags, idt_entry_struct* idt);
extern void load_idt(uint32_t);

#endif