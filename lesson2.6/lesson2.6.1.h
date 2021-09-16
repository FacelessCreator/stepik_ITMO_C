#include <stdint.h>
#include <stdlib.h>

// используйте typedef чтобы определить ftype
typedef size_t gtype(struct array, int64_t);
typedef char ftype (const float*, gtype);
