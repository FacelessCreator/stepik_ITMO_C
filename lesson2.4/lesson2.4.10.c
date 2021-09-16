#include "lesson2.4.9.c"
#include <inttypes.h>
#include <stdio.h>

struct maybe_int64 maybe_read_int64() {
    int64_t value;
    int result = scanf("%" SCNd64, &value);
    if (result == EOF) {
        return none_int64;
    } else {
        return some_int64(value);
    }
}

