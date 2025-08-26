ENTRY(_start)
SECTIONS
{
    .multiboot 0x100000 : AT(0x100000)
    {
        KEEP(*(.multiboot))
    }

    .text : { *(.text) }
    .rodata : { *(.rodata) }
    .data : { *(.data) }
    .bss : { *(.bss) }
}



