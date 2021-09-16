#include <stdint.h>
#include <stdlib.h>

int64_t* array_int_min( int64_t* array, size_t size ) {
    if (size == 0)
        return NULL;
 int64_t* min = array;
    for(size_t i = 0; i < size; ++i)
    {
        if (array[i] < *min)
            min = array+i;
    }
    return min;
}
