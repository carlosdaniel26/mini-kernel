; Declare constants for the multiboot header.
MBALIGN  equ  1 << 0            ; align loaded modules on page boundaries
MEMINFO  equ  1 << 1            ; provide memory map
MBFLAGS  equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + MBFLAGS)	; checksum of above, to prove we are multiboot

; Multiboot header
section .multiboot
align 4
	dd MAGIC
	dd MBFLAGS
	dd CHECKSUM
	dd 0, 0, 0, 0, 0

	dd 0
	dd 800
	dd 600
	dd 32

; Stack
section .bss
	align 16
	stack_bottom:
		resb 16384 * 8; 128 KiB 
	stack_top: ; after the 128 kib reserved for the stack

section .boot
global _start
_start:
	; configure stack
	mov esp, stack_top

	; the grub parameters are stored in eax and ebx, so have to pass them for the kernel_main function
    push eax
    push ebx
    ; Call the kernel
    extern kernel_main
	call kernel_main

	
; Clear interrupts and infinite loop just to code dont stop

	cli
.hang:	
	hlt
	jmp .hang
