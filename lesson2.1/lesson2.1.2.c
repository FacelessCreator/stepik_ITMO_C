#include <stdint.h>
#include <stdlib.h>

size_t count_zeroes(const void* data, size_t sz ) {
    size_t count = 0;
    for (size_t i = 0; i < sz; ++i)
    {
        const char* c = data+i;
        if (*c == 0)
            ++count;
    }
    return count;
}

