#include "idt.h"

idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

void set_idt_gate(int n, uint32_t handler) {
    idt[n].low_offset = low_16(handler);
    idt[n].seg_sel = KERNEL_CODE_SEG;
    idt[n].always0 = 0;
    idt[n].flags = 0x8e;
    idt[n].high_offset = high_16(handler);
}

void set_idt() {
    idt_reg.base = (uint32_t) &idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;

    asm __volatile__("lidt (%0)" : : "m" (idt_reg));
    //asm volatile ("sti");
    /* you must load idt_reg address so base and *limit* are included */
}
