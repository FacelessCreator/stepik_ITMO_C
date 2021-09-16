#define NULL 0

int predicate(int i) {
    // we don't really know what's inside
    return 1;
};

// position -- адрес указателя на первый элемент E в массиве,
// для которого predicate(E) выполняется.
// Функция возвращает 0 если элемент не найден.
int array_contains(int* array, int* limit, int** position) {
   for (int* i = array; i < limit; ++i) {
       if (predicate(*i)) {
           *position = i;
           return 1;    
       }
   }
   *position = NULL;
   return 0;
}