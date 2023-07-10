#pragma once

#include <stdlib.h>

namespace mem {
    void *alloc(u64 size);
    void *calloc(u64 size);
    void free(void *mem);
};
