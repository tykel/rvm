#include "common.h"

typedef struct mem_state s_mem_state;
typedef struct vpu_state s_vpu_state;

typedef struct cpu_state {
    /* Special-purpose registers. */
    rvmaddr_t   p;
    rvmaddr_t   s;
    uint16_t    f;

    /* General-purpose registers. */
    uint16_t    a;
    uint16_t    b;
    uint16_t    c;
    uint16_t    d;
    uint16_t    i;

    /* Links to other system components. */
    s_mem_state *mem;
    s_vpu_state *vpu;
} s_cpu_state;

typedef enum cpu_opc {
    CPU_OP_NOP, CPU_OP_MOVRR, CPU_OP_MOVRC, CPU_OP_MOVRCP, CPU_OP_MOVRCPBI,
    CPU_OP_MOVRCPWI, CPU_OP_MOVRRP, CPU_OP_MOVRRPBI, CPU_OP_MOVRRPWI,
    CPU_OP_MOVCPR, CPU_OP_MOVCPBIR, CPU_OP_MOVCPWIR, CPU_OP_MOVRPR,
    CPU_OP_MOVRPBIR, CPU_OP_MOVRPWIR,
    CPU_OP_INC, CPU_OP_IND, CPU_OP_DEC, CPU_OP_DED, CPU_OP_NOT, CPU_OP_ADD,
    CPU_OP_SUB,
    // TODO: Rest of opcodes
} e_cpu_opc;
