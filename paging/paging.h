#ifndef PAGING_H
#define PAGING_H

#include "../cpu/types.h"

void set_page_tables();
uint32_t translate_address(uint32_t addr);

#endif
