#include "lesson2.4.8.c"

void list_add_front( struct list** old, int64_t value );

// создать перевернутую копию списка
struct list* list_reverse(const struct list* list ) {
    struct list* new_list = NULL;
    while(list) {
        list_add_front(&new_list, list->value);
        list = list->next;
    }
    return new_list;
}