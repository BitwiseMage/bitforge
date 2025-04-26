#pragma once

#include "tracy/Tracy.hpp"

#if NDEBUG

#define BIT_TRACING
#define BIT_TRACING_NAMED(name)
#define BIT_TRACING_FRAME_START(name)
#define BIT_TRACING_FRAME_END(name)
#define BIT_TRACING_FRAME_NAMED(name)

#define BIT_MEM_TRACING_ALLOC(ptr)
#define BIT_MEM_TRACING_FREE(ptr)

#else

#define BIT_TRACING ZoneScoped
#define BIT_TRACING_NAMED(name) ZoneScopedN(name)
#define BIT_TRACING_FRAME_START(name) FrameMarkStart(name)
#define BIT_TRACING_FRAME_END(name) FrameMarkEnd(name)
#define BIT_TRACING_FRAME_NAMED(name) FrameMarkNamed(name)

#define BIT_MEM_TRACING_ALLOC(ptr, size) TracyAlloc(ptr, size)
#define BIT_MEM_TRACING_FREE(ptr) TracyFree(ptr)

#endif
