#pragma once

#include "tracing.h"

inline void* operator new(size_t size)
{
    BITFORGE_TRACING;

    if (size == 0)
    {
        return nullptr;
    }

    void* pointer = std::malloc(size);
    if (!pointer)
    {
        return nullptr;
    }

    BITFORGE_MEM_TRACING_ALLOC(pointer, size);
    return pointer;
}

inline void operator delete(void* pointer)
{
    BITFORGE_TRACING;
    BITFORGE_MEM_TRACING_FREE(pointer);
    std::free(pointer);
}
