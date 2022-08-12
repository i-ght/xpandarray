#include "xpandarray.h"

void xpandarray_construct(
    struct XpandArray* xpandarray,
    const size_t space_of_each_data_value,
    const size_t initial_data_value_space,
    const MemoryReallocate mem_realloc)
{

    const size_t initial_cap =
        space_of_each_data_value * initial_data_value_space;

    stream_construct(
        &xpandarray->data,
        initial_cap,
        mem_realloc
    );

    xpandarray->single_data_value_space = space_of_each_data_value;
}

void xpandarray_destruct(
    struct XpandArray* xpandarray)
{
    stream_destruct(&xpandarray->data);
    xpandarray->single_data_value_space = 0;
    xpandarray->data_value_count = 0;

}

bool xpandarray_contains(
    struct XpandArray* xpandarray,
    const void* data_value)
{
    for (ptrdiff_t i = 0; i < xpandarray->data_value_count; i++) {
        if (ZERO == 
            memcmp(
                data_value,
                &xpandarray->data.buffer[i * xpandarray->single_data_value_space],
                xpandarray->single_data_value_space
            )
        ) {
            return true;
        }
    }

    return false;
}



enum OKorERR xpandarray_add(
    struct XpandArray* xpandarray,
    void* data_value)
{
    if (ERR ==
        stream_write(
            &xpandarray->data,
            (const char*)data_value,
            xpandarray->single_data_value_space
        )
    ) {
        return ERR;
    }

    xpandarray->data_value_count++;
    return OK;
}


    