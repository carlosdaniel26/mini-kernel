#ifdef i686

#include <stdint.h>

typedef struct idt_entry_struct {
    uint16_t base_low;  // ISR's adress base low part
    uint16_t selector;  // GDT segment that the CPU will load into CS before calling the ISR
    uint8_t always0;
    uint8_t flags;      // attributes
    uint16_t base_high; // the higher 16 bits of the ISR's adress
}__attribute__((packed)) idt_entry_struct;

typedef struct idt_ptr_struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_ptr_struct;

void init_idt(void);

__attribute__((noreturn))
void set_idt_descriptor(uint8_t vector, void (*isr)(), uint8_t flags);

__attribute__((noreturn))
void init_irq();
#endif