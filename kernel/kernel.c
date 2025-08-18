#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../cpu/keyboard.h"
#include "../drivers/screen.h"

void kernel_main() {
    clear_screen();
    isr_install();
    init_timer(50);
    init_keyboard();
    asm volatile("sti");
}

