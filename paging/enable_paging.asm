global enable_paging
extern page_directory

enable_paging:
    mov eax, page_directory  ; load page directory address
    mov cr3, eax             ; set CR3
    mov eax, cr0
    or eax, 0x80000000       ; set PG bit
    mov cr0, eax
    ret
