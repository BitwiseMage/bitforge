#include "timer.h"

#include <SDL3/SDL_time.h>

int64_t TimerSubsystem::GetCurrentTimeInNanoseconds()
{
    int64_t ticks;
    SDL_GetCurrentTime(&ticks);
    return ticks;
}
