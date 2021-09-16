#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

#include "../lesson2.3/lesson2.3.4.c"

#define STACK_CAPACITY 100

struct vm_state {
  const union ins *ip;
  struct stack data_stack;
};

/* Вам уже доступны функции: */
bool stack_push( struct stack* s, int64_t value );
struct maybe_int64 stack_pop( struct stack* s );

/*
  struct maybe_int64 {
  int64_t value;
  bool valid;
  };
*/
struct maybe_int64 some_int64(int64_t i);
/*  const struct maybe_int64 none_int64; */



/*  Интерпретаторы команд */
void interpret_swap  ( struct vm_state* state )  {
  struct maybe_int64 a = stack_pop(&state->data_stack);
  struct maybe_int64 b = stack_pop(&state->data_stack);
    if (!a.valid || !b.valid)
        err("Not enough values for 'swap'");
    stack_push(&state->data_stack, a.value);
    stack_push(&state->data_stack, b.value);
}
void interpret_pop   ( struct vm_state* state )  {
  stack_pop(&state->data_stack);
}

void interpret_dup   ( struct vm_state* state )  {
  struct maybe_int64 a = stack_pop(&state->data_stack);
    if (!a.valid)
        err("Not enough values for 'dup'");
    stack_push(&state->data_stack, a.value);
    stack_push(&state->data_stack, a.value);
}

// Эти функции поднимают операции над числами на уровень стековых операций
// lift_unop применяет операцию к вершине стека;
void lift_unop( struct stack* s, int64_t (f)(int64_t))
{ 
    struct maybe_int64 a = stack_pop(s);
    if (!a.valid)
        err("Not enough values for unary operation");
    int64_t new_value = f(a.value);
    stack_push(s, new_value);
}

// lift_binop забирает из стека два аргумента,
// применяет к ним функцию от двух переменных и возвращает в стек результат
void lift_binop( struct stack* s, int64_t (f)(int64_t, int64_t))
{
    struct maybe_int64 b = stack_pop(s);
    struct maybe_int64 a = stack_pop(s);
    if (!a.valid || !b.valid)
        err("Not enough values for binaty operation");
    int64_t new_value = f(a.value, b.value);
    stack_push(s, new_value);
}


int64_t i64_add(int64_t a, int64_t b) { return a + b; }
int64_t i64_sub(int64_t a, int64_t b) { return a - b; }
int64_t i64_mul(int64_t a, int64_t b) { return a * b; }
int64_t i64_div(int64_t a, int64_t b) { return a / b; }
int64_t i64_cmp(int64_t a, int64_t b) { if (a > b) return 1; else if (a < b) return -1; return 0; }

int64_t i64_neg(int64_t a) { return -a; }

void interpret_iadd( struct vm_state* state ) { lift_binop(& state->data_stack, i64_add); }
void interpret_isub( struct vm_state* state ) { lift_binop(& state->data_stack, i64_sub); }
void interpret_imul( struct vm_state* state ) { lift_binop(& state->data_stack, i64_mul); }
void interpret_idiv( struct vm_state* state ) { lift_binop(& state->data_stack, i64_div); }
void interpret_icmp( struct vm_state* state ) { lift_binop(& state->data_stack, i64_cmp); }

void interpret_ineg( struct vm_state* state ) { lift_unop (& state->data_stack, i64_neg);  }