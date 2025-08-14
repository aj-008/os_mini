#ifndef ISR_H
#define ISR_H

#include "types.h"

typedef struct {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} registers_t;

void isr_install();
void isr_handler(registers_t *r);

#endif
