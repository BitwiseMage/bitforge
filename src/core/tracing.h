#pragma once

#include "tracy/Tracy.hpp"

#if NDEBUG

#define BITFORGE_TRACING
#define BITFORGE_TRACING_NAMED(name)
#define BITFORGE_TRACING_FRAME_START(name)
#define BITFORGE_TRACING_FRAME_END(name)
#define BITFORGE_TRACING_FRAME_NAMED(name)

#define BITFORGE_MEM_TRACING_ALLOC(ptr)
#define BITFORGE_MEM_TRACING_FREE(ptr)

#else

#define BITFORGE_TRACING ZoneScoped
#define BITFORGE_TRACING_NAMED(name) ZoneScopedN(name)
#define BITFORGE_TRACING_FRAME_START(name) FrameMarkStart(name)
#define BITFORGE_TRACING_FRAME_END(name) FrameMarkEnd(name)
#define BITFORGE_TRACING_FRAME_NAMED(name) FrameMarkNamed(name)

#define BITFORGE_MEM_TRACING_ALLOC(ptr, size) TracyAlloc(ptr, size)
#define BITFORGE_MEM_TRACING_FREE(ptr) TracyFree(ptr)

#endif
