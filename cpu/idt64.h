#ifndef IDT64_H
#define IDT64_H

#include "types.h"

#define KCODE_SEG 0x08
#define IDT_ENTRIES64 256

typedef struct {
    uint16_t low_offset;
    uint16_t seg_sel;
    uint8_t ist;
    uint8_t type_attr;
    uint16_t mid_offset;
    uint32_t high_offset;
    uint32_t zero;
}__attribute__((packed)) idt_entry_t;


typedef struct {
    uint16_t limit;
    uint64_t base;
}__attribute__((packed)) idtr_t;

void set_idt_entry(int n, uint64_t handler);
void set_idt64();

#endif
