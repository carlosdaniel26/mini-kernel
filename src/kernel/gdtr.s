.global gdt_flush

gdt_flush:
    mov %eax, 4(%esp)  /* Move the address of GDTR to EAX */
    lgdt (%eax)           /* Load GDTR using the address in EAX */

    mov %eax, 0x10      /* Select kernel data segment */
    mov %ds, %ax
    mov %es, %ax
    mov %fs, %ax
    mov %gs, %ax
    mov %ss, %ax

    jmp .flush    /* Jump to the return address in .flush */

.flush:
    ret
