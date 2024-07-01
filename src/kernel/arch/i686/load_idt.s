.global load_idt

load_idt:
    mov %eax, 4(%esp)
    lidt (%eax)
    ret
    