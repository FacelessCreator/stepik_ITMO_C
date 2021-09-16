#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>


struct list {
    int64_t value;
    struct list* next;
};

void print_int64(int64_t i);


/* Запустить функцию f на каждом элементе списка  */
void list_foreach(const struct list* l, void (f)(int64_t)) {
    while(l) {
        f(l->value);
        l = l->next;
    }
}

void print_int64_t(int64_t value) {
    printf("%" PRId64 " ", value);
}

/* Вывести список с помощью foreach и дополнительной функции */
void list_print(const struct list* l) { 
    list_foreach(l, print_int64_t);
}