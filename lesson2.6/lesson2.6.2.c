#include <stdint.h>
#include <stdlib.h>

// Мы хотим, чтобы в структуре user хранились ссылки только на строчки из кучи.
typedef struct { char* addr; } string_heap ;

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
string_heap halloc( const char* s ) {
    return (string_heap) {.addr = copy_string(s)};
}

void heap_string_free( string_heap h ) {
    free(h.addr);
}

/*  Тип для идентификаторов пользователей
    и его спецификаторы ввода и вывода для printf */
typedef uint64_t uid;
#define PRI_uid PRIu64
#define SCN_uid SCNu64

enum city {C_SARATOV, C_MOSCOW, C_PARIS, C_LOS_ANGELES, C_OTHER};

/*  Массив, где элементам перечисления сопоставляются их текстовые представления */
const char* city_string[] = {
  [C_SARATOV] = "Saratov",
  [C_MOSCOW] = "Moscow",
  [C_PARIS] = "Paris",
  [C_LOS_ANGELES] = "Los Angeles",
  [C_OTHER] = "Other"
};


struct user {
  const uid id;
  const string_heap name;
  enum city city;
};

int users_sort_uid_func(const void* a, const void* b) {
    struct user userA = *((struct user*) a);
        struct user userB = *((struct user*) b);
        if (userA.id > userB.id)
            return 1;
        else if (userB.id > userA.id)
            return -1;
        else
            return 0;
}

/* Сортировать массив пользователей по полю uid по возрастанию */
void users_sort_uid(struct user users[], size_t sz) {
    qsort(users, sz, sizeof(struct user), users_sort_uid_func);
}

int compare_strings(const string_heap a, const string_heap b) {
    size_t i = 0;
    while (a.addr[i] != 0 && b.addr[i] != 0) {
        if (a.addr[i] > b.addr[i])
            return 1;
        if (a.addr[i] < b.addr[i])
            return -1;
        ++i;
    }
    if (a.addr[i] != 0)
        return 1;
    if (b.addr[i] != 0)
        return -1;
    return 0;
}

int users_sort_name_func(const void* a, const void* b) {
    struct user userA = *((struct user*) a);
    struct user userB = *((struct user*) b);
    return compare_strings(userA.name, userB.name);
}

/* Сортировать массив пользователей по полю name */
/* Порядок строк лексикографический; можно использовать компаратор 
   строк -- стандартную функцию strcmp */
void users_sort_name(struct user users[], size_t sz) {
    qsort(users, sz, sizeof(struct user), users_sort_name_func);
}

int compare_cities(enum city cityA, enum city cityB) {
    string_heap cityA_name = halloc(city_string[cityA]);
    string_heap cityB_name = halloc(city_string[cityB]);
    int result = compare_strings(cityA_name, cityB_name);
    heap_string_free(cityA_name);
    heap_string_free(cityB_name);
    return result;
}

int compare_user_cities(const void* a, const void* b) {
    struct user userA = *((struct user*) a);
    struct user userB = *((struct user*) b);
    return compare_cities(userA.city, userB.city);
}

/* Сортировать массив по _текстовому представлению_ города */
void users_sort_city(struct user users[], size_t sz) {
    qsort(users, sz, sizeof(struct user), compare_user_cities);
}