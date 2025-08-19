#ifndef MEMORY_H
#define MEMORY_H

#include "../cpu/types.h"

void memory_copy(char *target, const char *source, int length);
void memory_set(uint8_t *d, uint8_t val, uint32_t len);

#endif
