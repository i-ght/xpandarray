#include "xpandarray.h"

static void* _realloc(void* address, const size_t size)
{
    if (ZERO == size) {
        return NULL;
    }

    void* ret = realloc(address, size);
    if (NULL == ret) {
        exit(1);
    }
    return ret;
}

int main(void)
{
    struct XpandArray array = {0};
    xpandarray_construct(
        &array,
        sizeof(int),
        0,
        _realloc
    );
    
    for (int i = 0; i < 999; i++) {
        if (ERR == xpandarray_add(&array, &i)) {
            return ERR;
        }
    }

    int i0 = 0;
    bool a = xpandarray_contains(&array, &i0);
    int i1 = 1000;
    bool b = xpandarray_contains(&array, &i1);

    return OK;
}