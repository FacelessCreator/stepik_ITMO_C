void swap(int* a, int* b) {
    int c = *a;
    *a = *b;
    *b = c;
}

void array_reverse(int* array, int size) {
    for (int i = 0; i < size/2; ++i) {
        swap(array+i, array+size-i-1);    
    }
}

void array_reverse_ptr(int* array, int* limit) {
    array_reverse(array, limit-array);
}