#include "kernel.h"
#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "../libc/string.h"
#include "../paging/paging.h"

void kernel_main() {
    clear_screen();
    isr_install();
    irq_install();
    /*set_page_tables();
    uint32_t x = translate_address(0x111);*/
    char s[1000];
    itoa(15, s, 2);
    kprint(s);
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
