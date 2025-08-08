print_hex:
    pusha
    
    mov cx, 0


hex_print_loop:
    cmp cx, 4
    je end

    mov ax, dx
    and ax, 0x000f ;keeps only last value
    add al, 0x30   ;get ASCII value
    cmp al, 0x39   ;
    jle step2
    add al, 0x07   ;A is ASCII 65-58 = 7


step2:
    mov bx, HEX_OUT + 5
    sub bx, cx          ;index intp string
    mov [bx], al
    ror dx, 4           ;4 right shift with wrap-around

    add cx, 1
    jmp hex_print_loop



end:
    mov bx, HEX_OUT
    call print
    popa
    ret



HEX_OUT:
    db '0x0000', 0





