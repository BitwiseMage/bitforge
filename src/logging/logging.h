#pragma once

#include "SDL3/SDL_log.h"
#include "core/tracing.h"

#define BITFORGE_LOG(fmt, ...) { BITFORGE_TRACING_NAMED("BITFORGE_LOG"); SDL_Log(fmt, __VA_ARGS__); }