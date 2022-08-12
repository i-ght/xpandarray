#ifndef _STREAM_H_
#define _STREAM_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#ifndef STREAM_MAX_BUFFER_SPACE
#define STREAM_MAX_BUFFER_SPACE (size_t)1134903170 /* 1 gigabyte ~ 1,134 megabytes */
#endif

#ifndef STREAM_DEFAULT_BUFFER_SIZE
#define STREAM_DEFAULT_BUFFER_SIZE 144
#endif

enum {ZERO=0};

#define PHI 1.618033989

enum OKorERR
{
    OK,
    ERR = -1
};

typedef void* (*MemoryAllocate)(const size_t size);

typedef void* (*MemoryReallocate)(
    void* address,
    const size_t size
);

/* Struct that contains a buffer that grows as it is written to. */
struct Stream 
{
    /* Length of the data written to the buffer. */
    size_t length;
    /* length of the buffer contained in this struct. */
    size_t space;
    /* pointer to the buffer. */
    char* buffer;
    
    MemoryReallocate mem_realloc;
};


enum OKorERR stream_realloc_buffer(
    struct Stream* stream,
    const size_t new_space
);

void stream_construct(
    struct Stream* stream,
    const size_t capacity,
    const MemoryReallocate mem_realloc
);

void stream_destruct(
    struct Stream* stream
);

enum OKorERR stream_write(
    struct Stream* stream,
    const char* data,
    const size_t required_space
);

enum OKorERR stream_write_cstr(
    struct Stream* stream,
    const char c_str[]
);

size_t stream_length(
    const struct Stream* stream
);

enum OKorERR stream_set_write_pos(
    struct Stream* stream,
    const size_t write_pos
);

enum OKorERR stream_copy_buffer(
    const struct Stream* stream,
    char** output,
    const MemoryAllocate mem_alloc
);

#endif