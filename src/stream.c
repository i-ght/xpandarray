#include "stream.h"

static enum OKorERR realloc_buffer(
    const size_t new_space,
    char** buffer,
    const MemoryReallocate mem_realloc)
{
    if (new_space > STREAM_MAX_BUFFER_SPACE) {
        return ERR;
    }

    char* tmp = 
        (char*)mem_realloc(
            *buffer,
            new_space
        );
    if (NULL == tmp) {
        return ERR;
    }
    
    *buffer = tmp;
    return OK;

}

void stream_construct(
    struct Stream* stream,
    const size_t capacity,
    const MemoryReallocate mem_realloc)
{
    stream->mem_realloc = mem_realloc;
    stream->buffer =  NULL;
    stream->length = ZERO;
    stream->space = capacity;
}


enum OKorERR stream_realloc_buffer(
    struct Stream* stream,
    const size_t new_space)
{
    if (ERR == 
        realloc_buffer(
            new_space,
            &stream->buffer,
            stream->mem_realloc
        )
    ) {
        return ERR;
    }

    stream->space = new_space;
    return OK;
}

void stream_destruct(
    struct Stream* stream)
{
    if (NULL != stream->buffer) {
        free(stream->buffer);
        stream->buffer = NULL;
    }

    stream->length = ZERO;
    stream->space = ZERO;    
}

enum OKorERR stream_write(
    struct Stream* stream,
    const char* data,
    const size_t required_space)
{
    if (NULL == data) {
        return ERR;
    }

    if (ZERO == required_space) {
        return ERR;
    }

    if (required_space > STREAM_MAX_BUFFER_SPACE) {
        return ERR;
    }

    ptrdiff_t remaining_space =
        stream->space - stream->length;

    while (remaining_space < required_space) {

        /* acquisition more space */
        if (ERR ==
            stream_realloc_buffer(
                stream,
                (stream->space <= STREAM_DEFAULT_BUFFER_SIZE ? STREAM_DEFAULT_BUFFER_SIZE : stream->space) * PHI
            )
        ) {
            return ERR;
        }

        remaining_space =
            stream->space - stream->length;
    }

    const ptrdiff_t i = stream->length;
    if (i < 0) {
        return ERR;
    }

    void* dest = (void*)&stream->buffer[i];
    const void* _ =
        memmove(
            dest,
            data,
            required_space
        );

    stream->length += required_space;

    return OK;
}

enum OKorERR stream_write_cstr(
    struct Stream* stream,
    const char c_str[])
{
    return
        stream_write(
            stream,
            c_str,
            strlen(c_str)
        );
}

size_t stream_length(
    const struct Stream* stream)
{
    return stream->length;
}

enum OKorERR stream_set_write_pos(
    struct Stream* stream,
    const size_t write_pos)
{
    if (write_pos >= stream->space) {
        return ERR;
    }
    stream->length = write_pos;

    return OK;
}

enum OKorERR stream_copy_buffer(
    const struct Stream* stream,
    char** output,
    const MemoryAllocate mem_alloc)
{
    char* tmp = (char*)mem_alloc(stream->length + 1);

    const void* _ =
        memmove(
            tmp,
            stream->buffer,
            stream->length
        );

    *output = tmp;

    return OK;
}