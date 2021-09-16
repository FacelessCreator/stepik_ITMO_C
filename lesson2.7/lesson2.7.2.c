#include "lesson2.7.1.c"

/* Изменить каждый элемент списка с помощью функции f  */
void list_map_mut(struct list* l, int64_t (f) (int64_t))  {
    while(l != NULL) {
        l->value = f(l->value);
        l = l->next;
    }
}


static int64_t triple( int64_t x ) { return x * 3; }

int64_t mult_int64_t(int64_t a) {return a*3;}

/* Используя list_map_mut умножьте все элементы списка на 3 */
void list_triple(struct list* l ) { 
    list_map_mut(l, &mult_int64_t);
}