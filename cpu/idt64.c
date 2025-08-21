#include "idt64.h"

idt_entry_t idt64[IDT_ENTRIES64];
idtr_t idtr;

void set_idt_entry(int idx, uint64_t handler) {
    idt64[idx].low_offset = low_16(handler);
    idt64[idx].seg_sel = KCODE_SEG;
    idt64[idx].ist = 0;
    idt64[idx].type_attr = 0x8e;
    idt64[idx].mid_offset = high_16(handler);
    idt64[idx].high_offset = (handler >> 32) & 0xFFFFFFFF;
}

void set_idt64() {
    idtr.base = (uint64_t) &idt64;
    idtr.limit = IDT_ENTRIES64 * sizeof(idt_entry_t) - 1;

    asm volatile("lidt (%0)" : : "m" (idtr));
}
    
