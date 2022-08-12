#ifndef _XPANDARRAY_H_
#define _XPANDARRAY_H_

#include <stdlib.h>
#include "continuum.h"

#ifndef MEM_STREAM_MAX_BUFFER_SIZE
#define MEM_STREAM_MAX_BUFFER_SIZE 1134903170U /* 1 gigabyte ~ 1,134 megabytes */
#endif

struct XpandArray
{
    size_t data_value_count;
    size_t single_data_value_space;
    struct Continuum data;
};

void xpandarray_construct(
    struct XpandArray* xpandarray,
    const size_t space_of_each_data_value,
    const MemoryReallocate mem_realloc,
    const MemoryFree mem_free
);

void xpandarray_destruct(
    struct XpandArray* xpandarray
);

bool xpandarray_contains(
    struct XpandArray* xpandarray,
    const void* data_value
);

int xpandarray_add(
    struct XpandArray* xpandarray,
    const void* data_value
);


#endif