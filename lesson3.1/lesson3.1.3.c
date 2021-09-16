#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

#include "../lesson2.3/lesson2.3.4.c"

#define STACK_CAPACITY 100

/* Описание инструкций (см. предыдущий шаг) */
enum opcode { BC_PUSH, BC_IPRINT, BC_IREAD, BC_IADD, BC_STOP };

struct bc_noarg {
  enum opcode opcode;
};
struct bc_arg64 {
  enum opcode opcode;
  int64_t arg;
};
union ins {
  enum opcode opcode;
  struct bc_arg64 as_arg64;
  struct bc_noarg as_noarg;
};

struct vm_state {
  const union ins *ip;
  struct stack data_stack;
};

/* Вам доступны:


struct maybe_int64 {
    int64_t value; 
    bool valid; 
};

struct maybe_int64 some_int64(int64_t i);

extern const struct maybe_int64 none_int64;

void maybe_int64_print( struct maybe_int64 i );
struct maybe_int64 maybe_read_int64();
void print_int64(int64_t i)
*/

void interpret_push(struct vm_state* state) {
  stack_push(& state->data_stack, state->ip->as_arg64.arg);
}

void interpret_iread(struct vm_state* state ) {
    struct maybe_int64 n = maybe_read_int64();
    if (!n.valid)
        err("Unexpected EOF");
    stack_push(& state->data_stack, n.value);
}
void interpret_iadd(struct vm_state* state ) {
    struct maybe_int64 a = stack_pop(&state->data_stack);
    struct maybe_int64 b = stack_pop(&state->data_stack);
    if (!a.valid || !b.valid)
        err("Not enough values for 'add'");
    stack_push(& state->data_stack, a.value+b.value);
}
void interpret_iprint(struct vm_state* state ) {
    struct maybe_int64 n = stack_pop(&state->data_stack);
    if (!n.valid)
        err("Not enough values for 'print'");
    print_int64(n.value);
}

/* Подсказка: можно выполнять программу пока ip != NULL,
    тогда чтобы её остановить достаточно обнулить ip */
void interpret_stop(struct vm_state* state ) {
  state->ip = NULL;
}

typedef void (*interpreter_func)(struct vm_state*);

const interpreter_func interpreters[] = {
  [BC_PUSH] = interpret_push,
  [BC_IREAD] = interpret_iread,
  [BC_IADD] = interpret_iadd,
  [BC_IPRINT] = interpret_iprint,
  [BC_STOP] = interpret_stop
};

void interpret(struct vm_state* state) {
    union ins* ip_start = state->ip;
    while(true) {
        enum opcode current_opcode = state->ip->opcode;
        (interpreters[current_opcode]) (state);
        if (state->ip == NULL)
            break;
        ++state->ip;
    }
}