
disk_load:
    pusha
    push dx

    mov ah, 0x02
    mov al, dh   ;number of sectors to read
    mov cl, 0x02 ;second sector (after boot sector)
    mov ch, 0x00
    mov dh, 0x00

    int 0x13     ;read interrupt
    jc disk_error

    pop dx
    cmp al, dh
    jne sector_error
    popa
    ret



disk_error:
    mov bx, DISK_ERROR
    call print
    call print_newline
    mov dh, ah         ;error code
    call print_hex
    jmp disk_loop

sector_error:
    mov bx, SECTOR_ERROR
    call print


disk_loop:
    jmp $


DISK_ERROR:
    db "Disk read error", 0

SECTOR_ERROR:
    db "Incorrect number of sectors read", 0
