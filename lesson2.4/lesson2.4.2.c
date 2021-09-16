#include <stdint.h>
#include <stdlib.h>

struct heap_string {
  char* addr;
};

size_t string_length(const char* s) {
    size_t length = 0;
    while(*s != 0) {
        ++length;
        ++s;
    }
    return length;
}

char* copy_string(const char* s) {
    size_t length = string_length(s);
    char* result = malloc(sizeof(char)*(length+1));
    for (size_t i = 0; i <= length; ++i) {
        result[i] = s[i];
    }
    return result;
}

// скопировать в кучу
struct heap_string halloc( const char* s ) {
    return (struct heap_string) {.addr = copy_string(s)};
}

// освободить память
void heap_string_free( struct heap_string h ) {
    free(h.addr);
}