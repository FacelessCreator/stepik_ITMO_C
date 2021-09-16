#include "lesson2.4.4.c"

struct list* list_last(struct list* list) {
    struct list* last = NULL;
    while(list != NULL) {
        last = list;
        list = list->next;
    }
    return last;
}
