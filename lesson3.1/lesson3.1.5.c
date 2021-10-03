#include "lesson3.1.4.c"

enum ins_arg_type { IAT_NOARG, IAT_I64 };

struct ins_descr {
  const char*       mnemonic;     // мнемоника
  enum ins_arg_type argtype;      // тип аргументов: 0, 1 численных аргументов
  bool              affects_ip;   // изменяет ли инструкция IP?

// Новые поля:
  size_t            stack_min;    // минимальное количество элементов для инструкции
  int64_t           stack_delta;  // сколько требуется аргументов в стеке
};

// ----------

void interpret(struct vm_state* state, ins_interpreter * const  (actions)[]) {
  for (; state->ip ;) {
    const union ins* ins = state->ip;

    const struct ins_descr* ins_descr = instructions + ins->opcode;

      //printf("%" PRId64 " > %" PRId64 " == %d\n", state->data_stack.count + ins_descr->stack_delta, state->data_stack.data.size, ((int64_t)state->data_stack.count + (int64_t)ins_descr->stack_delta) > (int64_t)state->data_stack.data.size);
      
    if (((int64_t)state->data_stack.count + (int64_t)ins_descr->stack_delta) > (int64_t)state->data_stack.data.size) {
        printf("Stack overflow\n");
        break;
    }
      
    if (state->data_stack.count < ins_descr->stack_min) {
        printf("Stack underflow\n");
        break;
    }

    actions[ins->opcode](state);

    if (!ins_descr->affects_ip) { state->ip = state->ip + 1; }
  }
}