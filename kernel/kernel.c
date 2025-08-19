#include "kernel.h"
#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "../libc/string.h"

void kernel_main() {
    clear_screen();
    isr_install();
    irq_install();
}

void user_input(char *input) {
    if (strcmp(input, "END") == 0) {
        kprint("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    }
    kprint("You said: ");
    kprint(input);
    kprint("\n> ");
}
