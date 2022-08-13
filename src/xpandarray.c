#include "xpandarray.h"

enum {ZERO=0};
enum {ERR=-1,OK=0};

void xpandarray_construct(
    struct XpandArray* xpandarray,
    const size_t space_of_each_data_value,
    const MemoryReallocate mem_realloc,
    const MemoryFree mem_free)
{
    continuum_construct(
        &xpandarray->data,
        mem_realloc,
        mem_free
    );

    xpandarray->single_data_value_space = space_of_each_data_value;
}

void xpandarray_destruct(
    struct XpandArray* xpandarray)
{
    continuum_destruct(&xpandarray->data);
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
                &xpandarray->data.spacetime[
                    i * xpandarray->single_data_value_space
                ],
                xpandarray->single_data_value_space
            )
        ) {
            return true;
        }
    }

    return false;
}

int xpandarray_add(
    struct XpandArray* xpandarray,
    const void* data_value)
{
    if (ERR ==
        continuum_write(
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


    