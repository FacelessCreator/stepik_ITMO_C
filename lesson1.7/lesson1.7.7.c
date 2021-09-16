#include <stdbool.h>

bool is_whitespace(char c) { return c == ' ' || c == '\t' || c == '\n'; }

int string_count(char* str) { 
   int len = 0;
    while (*(str+len) != 0) {
        ++len;
    }
    return len;
}

int string_words(char* str)  {
    int changes_count = 0; // count of change 'is_whitespace' function value
    char* i = str;
    while(*i != 0) {
        if (is_whitespace(*i) != (is_whitespace(*(i+1)) || *(i+1) == 0))
            ++changes_count;
        ++i;
    }
    return (changes_count+1) / 2;
}