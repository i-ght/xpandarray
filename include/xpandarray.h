#ifndef _XPANDARRAY_H_
#define _XPANDARRAY_H_

#include <stdlib.h>
#include "stream.h"

#ifndef MEM_STREAM_MAX_BUFFER_SIZE
#define MEM_STREAM_MAX_BUFFER_SIZE 1134903170U /* 1 gigabyte ~ 1,134 megabytes */
#endif

struct XpandArray
{
    size_t data_value_count;
    size_t single_data_value_space;
    struct Stream data;
};

void xpandarray_construct(
    struct XpandArray* xpandarray,
    const size_t size_of_each_data_value,
    const size_t initial_buffer_size,
    const MemoryReallocate mem_realloc
);

void xpandarray_destruct(
    struct XpandArray* xpandarray
);

bool xpandarray_contains(
    struct XpandArray* xpandarray,
    const void* data_value
);

enum OKorERR xpandarray_add(
    struct XpandArray* xpandarray,
    void* data_value
);


#endif