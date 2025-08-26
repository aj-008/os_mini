#include "paging.h"

extern void enable_paging(uint32_t *page_directory_address);

uint32_t page_directory[1024]__attribute__((aligned(4096)));
uint32_t first_page_table[1024]__attribute__((aligned(4096)));

void set_page_tables() {

    for (int i = 0; i < 1024; i++) {
        page_directory[i] = 0x00000002;        
    }
    for (int i = 0; i < 1024; i++) {
        first_page_table[i] = (i * 0x1000) | 0x03;
    }
    page_directory[0] = (unsigned int)first_page_table | 0x03;

    enable_paging(page_directory);
}





/* translate_address
 * Returns physical address of addr
 */
uint32_t translate_address(uint32_t addr) {
    uint32_t dir_ind = (addr >> 22) & 0x3ff;
    uint32_t table_ind = (addr >> 12) & 0x3ff;
    uint32_t offset = addr & 0xfff;

    uint32_t PDE = page_directory[dir_ind];
    uint32_t *PT = (uint32_t *)(PDE & 0xfffff000);
    uint32_t PTE = PT[table_ind];
    
    return (PTE & 0xfffff000) + offset;
}

