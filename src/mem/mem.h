#include "common.h"

static const size_t MEM_BANK_SIZE  0x2000

typedef struct mem_state {
    /* */
    uint8_t rom_fixed[MEM_BANK_SIZE];
    uint8_t *rom_bnksw;
    
    /* The RAM banks are fixed. */
    uint8_t ram_0[MEM_BANK_SIZE];
    uint8_t ram_1[MEM_BANK_SIZE];


} s_mem_state;
