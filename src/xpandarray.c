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

bool xpandarray_tryfind(
    struct XpandArray* xpandarray,
    const XpandArrayPredicate predicate,
    const void* user_data,
    void** value)
{
    for (ptrdiff_t i = 0; i < xpandarray->data_value_count; i++) {
        const ptrdiff_t index = 
            i * xpandarray->single_data_value_space;
        void* val = &xpandarray->data.spacetime[index];
        if (predicate(
                val,
                xpandarray->single_data_value_space,
                user_data
            )
        ) {
            if (NULL != value) {
                *value = val;
            }
            return true;
        }

    }

    return false;
}

static bool value_is_equal(
    const void* array_value,
    const size_t array_value_length,
    const void* user_data)
{
    if (ZERO == 
        memcmp(
            array_value,
            user_data,
            array_value_length
        )
    ) {
        return true;
    }
    return false;
}

bool xpandarray_contains(
    struct XpandArray* xpandarray,
    const void* data_value)
{
    return xpandarray_tryfind(
        xpandarray,
        value_is_equal,
        data_value,
        NULL
    );

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


    