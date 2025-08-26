#include "isr.h"
#include "idt.h"
#include "../drivers/screen.h"
#include "ports.h"
#include "../libc/string.h"
#include "../drivers/keyboard.h"
#include "timer.h"


/* Stubs declared in interrupt.asm, 
 * contain list of addresses to be assigned functions
 */
extern void* isr_stub_table[];
extern void* irq_stub_table[];


/* Set of handler function addresses (function pointers)
 * -- void (*isr_t)(registers_t *) --
 */
isr_t interrupt_handlers[256];



void isr_install() {
    for (uint8_t i = 0; i < 32; i++) {
        set_idt_gate(i, (uint32_t)isr_stub_table[i]);
    }

    pic_remap();

    for (uint8_t i = 0; i < 16; i++) {
        set_idt_gate(32 + i, (uint32_t)irq_stub_table[i]);
    }

    set_idt();
}

void irq_install() {
    asm volatile("sti");
    init_timer(50);
    init_keyboard();
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

const char *exception_messages[] = {
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
    char s[16];
    itoa(r->int_no, s, 10);
    kprint(s);
    kprint("\n");
    kprint(exception_messages[1]);
    kprint(exception_messages[r->int_no]);
    kprint("\n");
}

void register_interrupt_handler(uint8_t n, isr_t handler) {
    interrupt_handlers[n] = handler;
}


void irq_handler(registers_t *r) {
    if (r->int_no >= 40) port_outb(0xA0, 0x20);
    port_outb(0x20, 0x20);

    if (interrupt_handlers[r->int_no] != 0) { 
        interrupt_handlers[r->int_no](r);
    }
}
