#include "lesson2.4.5.c"

void list_add_back( struct list** old, int64_t value ) {
    struct list* last_node = list_last(*old);
    struct list* new_node = node_create(value);
    if (last_node != NULL)
        last_node->next = new_node;
    else
        *old = new_node;
}

