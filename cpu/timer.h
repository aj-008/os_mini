#ifndef TIMER_H
#define TIMER_H

#include "../kernel/util.h"
#include "isr.h"
#include "types.h"

void init_timer(uint32_t freq);
static void timer_callback(registers_t r);

#endif
