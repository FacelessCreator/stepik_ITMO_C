#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

enum opcode { 
  BC_PUSH, BC_POP, BC_SWAP, BC_DUP,
  BC_IADD, BC_ISUB, BC_IMUL, BC_IDIV, 
  BC_INEG,
  BC_IPRINT, BC_IREAD, 
  BC_ICMP, 
  BC_STOP 
};

struct bc_noarg { enum opcode opcode; };
struct bc_arg64 { enum opcode opcode; int64_t arg; };

union ins { 
   enum opcode opcode; 
   struct bc_arg64 as_arg64; 
   struct bc_noarg as_noarg;
};

/* Программа: */

const union ins program[] = {
    {BC_IREAD},
    { .as_arg64 = { BC_PUSH, .arg = 10 } },
    {BC_ISUB},
    { .as_arg64 = { BC_PUSH, .arg = 2 } },
    {BC_IDIV},
    {BC_IPRINT},
    {BC_STOP}
};
