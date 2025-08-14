#include "isr.h"
#include "idt.h"
#include "../drivers/screen.h"
#include "../kernel/util.h"

extern void *isr_stub_table[];


void isr_install() {
    for (int i = 0; i < 32; i++) {
        set_idt_gate(i, (uint32_t)isr_stub_table[i]);
    }
    set_idt();
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

void isr_handler(registers_t *r) {
    kprint("received interrupt: ");
    char s[3];
    itoa(r->int_no, s, 10);
    kprint(s);
    kprint("\n");
    kprint(exception_messages[r->int_no]);
    kprint("\n");
}
