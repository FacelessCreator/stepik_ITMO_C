#include "lesson2.4.7.c"

#include "stdbool.h"

struct maybe_int64 {
  bool valid;
  int64_t value;
};

struct maybe_int64 some_int64( int64_t i ) {
  return (struct maybe_int64) { .value = i, .valid = true };
}

const struct maybe_int64 none_int64 = { 0 };

struct maybe_int64 list_at(const struct list* list, size_t idx ) {
    size_t pos = 0;
    while (pos != idx) {
        if (list == NULL) {
            return none_int64;
        }
        list = list->next;
        ++pos;
    }
    if (list == NULL) {
        return none_int64;
    }
    return some_int64(list->value);
}


