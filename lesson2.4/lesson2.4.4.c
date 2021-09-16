#include "lesson2.4.3.c"

struct list* list_get_pre_last(struct list* list) {
    struct list* pre_last = NULL;
    struct list* last = NULL;
    while(list != NULL) {
        pre_last = last;
        last = list;
        list = list->next;
    }
    return pre_last;
}

void list_destroy_last(struct list** list) {
    struct list* pre_last = list_get_pre_last(*list);
    if (pre_last != NULL) {
        free(pre_last->next);
        pre_last->next = NULL;
    } else {
        free(*list);
        *list = NULL;
    }
}

void list_destroy( struct list* list ) {
    while(list != NULL) {
        list_destroy_last(&list);
    }
}




