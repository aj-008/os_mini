[org 0x7c00]
KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl
mov bp, 0x9000
mov sp, bp

mov bx, REAL_MESSAGE
call print
call print_nl

call load_kernel
call switch_to_pm
jmp $


%include 'boot/print.asm'
%include 'boot/print_32.asm'
%include 'boot/print_hex.asm'
%include 'boot/gdt.asm'
%include 'boot/switch_pm.asm'
%include 'boot/disk.asm'

[bits 16]
load_kernel:
    mov bx, KERNEL_MESSAGE
    call print
    call print_nl

    mov bx, KERNEL_OFFSET
    mov dh, 16
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]
BEGIN_PM:
    mov ebx, PROTECTED_MESSAGE
    call print_string_pm
    call KERNEL_OFFSET
    hang:
        hlt
        jmp hang


BOOT_DRIVE:
    db 0
REAL_MESSAGE:
    db "hello. we are starting in real mode", 0
PROTECTED_MESSAGE:
    db "WE MADE IT TO PROT MODE!!", 0
KERNEL_MESSAGE:
    db "Loading kernel into memory...", 0


times 510 - ($-$$) db 0
dw 0xaa55
