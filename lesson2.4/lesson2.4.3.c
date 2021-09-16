#include <stdint.h>
#include <stdlib.h>

struct list {
   int64_t value;
   struct list* next;
};

size_t list_length(const struct list* list ) {
    size_t len = 0;
    while(list != NULL) {
        ++len;
        list = list->next;
    }
    return len;
}