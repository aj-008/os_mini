#include "timer.h"
#include "../drivers/screen.h"
#include "../kernel/util.h"
#include "../drivers/ports.h"


volatile uint32_t tick = 0;  /* i dont like this */

static void timer_callback(registers_t r) {
    tick++;
    kprint("Tick: ");
    char s[256];
    itoa(tick, s, 10);
    kprint(s);
    kprint("\n");
}

void init_timer(uint32_t freq) {
    register_interrupt_handler(IRQ0, timer_callback);

    /*  check this */

    /* Get the PIT value: hardware clock at 1193180 Hz */
    uint32_t divisor = 1193180 / freq;
    uint8_t low  = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)( (divisor >> 8) & 0xFF);
    /* Send the command */
    port_outb(0x43, 0x36); /* Command port */
    port_outb(0x40, low);
    port_outb(0x40, high);
}
