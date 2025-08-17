#include "isr.h"
#include "idt.h"
#include "types.h"
#include "../drivers/screen.h"
#include "../drivers/ports.h"
#include "../kernel/util.h"

#define ISR_ENTRIES 256

extern void *isr_stub_table[];
extern void *irq_stub_table[];

isr_t interrupt_handlers[ISR_ENTRIES];


void isr_install() {
    for (int i = 0; i < 32; i++) {
        set_idt_gate(i, (uint32_t)isr_stub_table[i]);
    }

    pic_remap();
    for (int i = 32; i < 47; i++) {
        set_idt_gate(i, (uint32_t)irq_stub_table[i]);
    }

    set_idt();
}

void pic_remap() {
    port_outb(0x20, 0x11);
    port_outb(0xA0, 0x11);
    port_outb(0x21, 0x20);
    port_outb(0xA1, 0x28);
    port_outb(0x21, 0x04);
    port_outb(0xA1, 0x02);
    port_outb(0x21, 0x01);
    port_outb(0xA1, 0x01);
    port_outb(0x21, 0x0);
    port_outb(0xA1, 0x0); 
}



char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isr_handler(registers_t r) {
    uint32_t int_no = r.int_no;
    kprint("received interrupt: ");
    char s[4];
    itoa(int_no, s, 10);
    kprint(s);
    kprint("\n");
    kprint(exception_messages[int_no]);
    kprint("\n");
}


void register_interrupt_handler(uint8_t n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

void irq_handler(registers_t r) {
    if (r.int_no >= 40) port_outb(0xA0, 0x20); /* activate slave PIC */
    port_outb(0x20, 0x20);                     /* activate master PIC always */

    if (interrupt_handlers[r.int_no] != 0) {
        isr_t handler = interrupt_handlers[r.int_no];
        handler(r);
    }
}




