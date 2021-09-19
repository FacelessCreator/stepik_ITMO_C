#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

// Почему тут используется typedef:
// https://stepik.org/lesson/499140/step/12
typedef struct {
  int64_t value;
} item;

#define STACK_ITEM_PRI PRId64

struct maybe_item {
  bool valid;
  item value;
};

static const struct maybe_item none_int = {0, {0}};

static struct maybe_item some_int(int64_t value) {
  return (struct maybe_item){true, {value}};
}
 
struct stack_int;

struct stack_int *stack_int_create();

void stack_int_destroy(struct stack_int *s);

bool stack_int_empty(struct stack_int const *s);
bool stack_int_full(struct stack_int const *s);

bool              stack_int_push(struct stack_int *s, item i);
struct maybe_item stack_int_pop(struct stack_int *s);

void stack_int_print(struct stack_int const *s);

// ----------

struct list {
  item value;
  struct list *next;
};

struct stack_int {
  struct list *items;
};

static struct list *c(item i, struct list *next) {
  struct list *result = malloc(sizeof(struct list));
  *result = (struct list){i, next};
  return result;
}

static struct maybe_item p(struct list** l) {
    struct list* first_node = *l;
    if (first_node == NULL)
        return none_int;
    item value = first_node->value;
    *l = first_node->next;
    free(first_node);
    return some_int(value.value);
}

static struct stack_int stack_int_default() {
  return (struct stack_int){.items = NULL};
}

struct stack_int *stack_int_create() {
  struct stack_int *const result = malloc(sizeof(struct stack_int));
  *result = stack_int_default();
  return result;
}

static void list_free( struct list* l ) {
  while (l) {
    struct list *cur = l;
    l = l->next;
    free(cur);
    }
}

void stack_int_destroy(struct stack_int *s) {
 list_free(s->items);
    free(s);
}

bool stack_int_empty(struct stack_int const *s) { 
 return s->items == NULL;
}

bool stack_int_full(struct stack_int const *s) { 
 return s->items != NULL;
}

bool stack_int_push(struct stack_int *s, item i) {
 s->items = c(i, s->items);
   return true;
}

struct maybe_item stack_int_pop(struct stack_int *s) {
  return p(&(s->items));
}

static void stack_int_foreach(struct stack_int const *s, void (f)(item)) {
  for (struct list *l = s->items; l; l = l->next)
    f(l->value);
}

static void print_int64_cr(item i) { printf("%" STACK_ITEM_PRI "\n", i.value); }

// Заметьте, что и здесь мы смогли оставить функцию "как есть"
// просто переписав foreach, через который она реализована
// Это показывает, что обход разных структур данных, свертки (fold)
// и другие популярные функции высшего порядка на самом деле изолируют кусочек
// логики, отличающие работу с одними и теми же данными, структурироваными по-разному.
// Строгое обоснование этого дают теория категорий и алгебраические типы данных.
void stack_int_print(struct stack_int const *s) {
  stack_int_foreach( s, print_int64_cr );
}