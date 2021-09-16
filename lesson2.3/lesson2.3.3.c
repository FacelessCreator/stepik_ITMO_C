#include "lesson2.3.2.c"

void array_int_fill( int64_t* array, size_t sz );

struct array_int array_int_read();
struct maybe_int64 array_int_get( struct array_int a, size_t i );
bool array_int_set( struct array_int a, size_t i, int64_t value );
void array_int_print( struct array_int array );
struct maybe_int64 array_int_min( struct array_int array );
void array_int_free( struct array_int a );

void array_int_normalize( struct array_int array, int64_t m ) {
  for (size_t i = 0; i < array.size; i = i + 1) {
    array.data[i] = array.data[i] - m;
  }
}

/*  ---- maybe int[] ---- */

struct maybe_array_int {
  struct array_int value;
  bool valid;
};

struct maybe_array_int some_array_int(struct array_int array) {
  return (struct maybe_array_int) { array, true };
}
const struct maybe_array_int none_array_int = { {NULL, 0}, false };


/*  ---- int[][] ---- */

struct array_array_int {
  struct array_int* data;
  size_t size;
};

/*  --- строки ---  */

struct maybe_array_int array_array_int_get_row( struct array_array_int a, size_t i ) {
  if ( 0 <= i && i < a.size ) { return some_array_int( a.data[i] ); }
  else { return none_array_int; }
}

bool array_array_int_set_row( struct array_array_int a, size_t i, struct array_int value ) {
  if (0 <= i && i < a.size) {
    a.data[i] = value;
    return true;
  }
  else { return false; }
}

/*  --- get/set ---  */

struct maybe_int64 array_array_int_get( struct array_array_int a, size_t i, size_t j ) {
    struct maybe_array_int row = array_array_int_get_row(a, i);
    if (!row.valid)
        return (struct maybe_int64) {0};
    else
        return array_int_get(row.value, j);
}

bool array_array_int_set( struct array_array_int a, size_t i, size_t j, int64_t value ) {
  struct maybe_array_int row = array_array_int_get_row(a, i);
    if (!row.valid)
        return false;
    return array_int_set(row.value, j, value);
}

/*  --- read/print ---  */

struct array_array_int array_array_int_read() {
    struct array_array_int array = {
        .size = read_size(),
        .data = NULL                               
    };
    if (array.size > 0) {
        array.data = malloc(sizeof(struct array_int)*array.size);
        for (size_t i = 0; i < array.size; ++i) {
            array.data[i] = array_int_read();
        }
    }
    return array;
}


void array_array_int_print( struct array_array_int array) {
  for (size_t i = 0; i < array.size; ++i) {
      struct maybe_array_int row = array_array_int_get_row(array, i);
      if (row.valid) {
          array_int_print(row.value);
      }
      printf("\n");
  }
}


/*  --- min/normalize ---  */

// найти минимальный элемент в массиве массивов
struct maybe_int64 array_array_int_min( struct array_array_int array ) {
    struct maybe_int64 result = {0};
    for (size_t i = 0; i < array.size; ++i) {
        struct maybe_int64 local_min = array_int_min(array.data[i]);
        if (local_min.valid) {
            if (!result.valid || result.value > local_min.value) {
                result = local_min;
            }
        }
    }
    return result;
}

// вычесть из всех элементов массива массивов число m
void array_array_int_normalize( struct array_array_int array, int64_t m) {
  for (size_t i = 0; i < array.size; i = i + 1) {
    const struct maybe_array_int cur_row = array_array_int_get_row( array, i );
    if (cur_row.valid) {
         array_int_normalize( cur_row.value, m );
    }
  }
}

void array_array_int_free( struct array_array_int array ) {
  for (size_t i = 0; i < array.size; ++i) {
      array_int_free(array.data[i]);
  }
  free(array.data);
}