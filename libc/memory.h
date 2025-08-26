#ifndef MEMORY_H
#define MEMORY_H

#include "../cpu/types.h"

void memory_copy(char *target, const char *source, int length);
void memory_set(char *d, char val, uint32_t len);

#endif
