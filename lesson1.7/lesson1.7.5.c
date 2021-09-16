void array_fib(int* array, int* limit) {
    if (limit-array <= 0) {
        return;    
    }
    array[0] = 1;
    if (limit-array == 1) {
        return;    
    }
    array[1] = 1;
    for (int* i = array+2; i < limit; ++i) {
        *i = *(i-1) + *(i-2);
    }
}