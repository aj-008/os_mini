#include "../drivers/screen.h"
#include "util.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"

void kernel_main() {
    clear_screen();

    isr_install();
    asm volatile("int $0");
    asm volatile("int $2");
}

