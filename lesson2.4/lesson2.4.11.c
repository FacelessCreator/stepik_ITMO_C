#include "lesson2.4.10.c"

struct list* list_read() {
    struct list* start_node = NULL;
    struct list* list = NULL;
    struct maybe_int64 new_value = maybe_read_int64();
    while (new_value.valid) {
        struct list* new_node = node_create(new_value.value);
        if (!list) {
            list = new_node;
            start_node = list;
        }
        else
        {
            list->next = new_node;
            list = new_node;
        }
        new_value = maybe_read_int64();
    }
    return start_node;
}

