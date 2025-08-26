MB_ALIGN          equ 1 << 0
MB_MEMINFO        equ 1 << 1
MB_FLAGS          equ MB_ALIGN | MB_MEMINFO
MB_MAGIC_NUMBER   equ 0x1badb002
MB_CHECKSUM       equ -(MB_MAGIC_NUMBER + MB_FLAGS)


section .multiboot
align 4
multiboot_header:
    dd MB_MAGIC_NUMBER
    dd MB_FLAGS
    dd MB_CHECKSUM

section .bss
align 16
stack_bottom:
resb 16384
stack_top:

section .text
global _start
extern kmain
_start:
    mov esp, stack_top
    call kmain
    cli
    hlt
    jmp $


