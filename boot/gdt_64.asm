gdt64:
    dq 0x0000000000000000         ; null
    dq 0x00af9a000000ffff         ; kernel code
    dq 0x00af92000000ffff         ; kernel data
    dq 0x00affa000000ffff         ; user code
    dq 0x00aff2000000ffff         ; user data
    dq 0x0000000000000000         ; tss
    dq 0x0000000000000000         ; tss

gdt64_descriptor:
    dw gdt64_descriptor - gdt64 - 1
    dq gdt64
