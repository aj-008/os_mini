#include "timer.h"
#include "ports.h"
#include "../drivers/screen.h"
#include "../libc/string.h"
#include "isr.h"

uint32_t tick = 0;

static void timer_callback(registers_t *r) {
    tick++;
    //kprint("Tick: ");
    
    char tick_ascii[256];
    itoa(tick, tick_ascii, 10);
    //kprint(tick_ascii);
    //kprint("\n");
}

void init_timer(uint32_t freq) {
    /* Install the function we just wrote */
    register_interrupt_handler(IRQ0, timer_callback);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    uint32_t divisor = 1193180 / freq;
    uint8_t low  = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)( (divisor >> 8) & 0xFF);

    port_outb(0x43, 0x36); /* Command port */
    port_outb(0x40, low);
    port_outb(0x40, high);
}
