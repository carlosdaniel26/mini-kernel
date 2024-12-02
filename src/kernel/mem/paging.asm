section.bss
align 4096

global configure_paging_directories

p4_table:
    resb 4096

p3_table:
    resb 4096

p2_table:
    resb 4096

p1_table:
    resb 4096

configure_paging_directories:

    ; p4[0] -> p3
    mov eax,    p3_table        ; get p3_table address
    or  eax,    0b11            ; set present and write bits on eax
    mov dword  [p4_table], eax

    ; p3[0] -> p2
    mov eax,    p2_table        ; get p2_table address
    or  eax,    0b11            ; set present and write bits on eax
    mov dword  [p3_table], eax

    ; p2[0] -> p1
    mov eax,    p2_table        ; get p1_table address
    or  eax,    0b11            ; set present and write bits on eax
    mov dword  [p1_table], eax