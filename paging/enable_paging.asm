global enable_paging

enable_paging:
    push ebp
    mov ebp, esp
    mov eax, [esp + 8]
    mov cr3, eax             ; Load directory address
    mov eax, cr0
    or eax, 0x80000000       ; Set PG bit
    mov cr0, eax
    mov esp, ebp
    pop ebp
    ret
