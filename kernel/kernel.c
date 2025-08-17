#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"

void kernel_main() {
    isr_install();
    /* Test the interrupts */
    __asm__ __volatile__("int $0");
    __asm__ __volatile__("int $3");
}

