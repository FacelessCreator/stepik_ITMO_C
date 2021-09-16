#include <stdint.h>
#include <stdlib.h>

#define LIMIT 100

// Определите массив в котором будут 8*1024*1024 чисел
// Массив не должен занимать больше 40 МБ памяти

uint32_t data[8*1024*1024] = {0};

// Определите функцию count_gt
// Она должна вернуть количество чисел в data, которые больше LIMIT
// LIMIT это определение препроцессора, оно вам уже доступно
// скрытый от вас код заполнит массив data числами и проверит правильность
// вашей функции
size_t count_gt(uint32_t* array, size_t size) {
size_t count = 0;
    for(size_t i = 0; i < size; ++i)
    {
        if (array[i] > LIMIT)
            ++count;
    }
    return count;
}