#include "timer.h"

#include <SDL3/SDL_time.h>

void TimerSubsystem::MarkStartWork()
{
    BIT_TRACING;
    m_current_frame_start_work_time = GetCurrentTimeInNanoseconds();
}

void TimerSubsystem::MarkEndWork()
{
    BIT_TRACING;
    PossibleSleep();
    FrameFinished();
}

void TimerSubsystem::PossibleSleep() const
{
    BIT_TRACING;
    if (m_minimum_frame_time == 0)
    {
        return;
    }

    while (GetCurrentTimeInNanoseconds() - m_current_frame_start_work_time < m_minimum_frame_time);
}

void TimerSubsystem::FrameFinished()
{
    BIT_TRACING;
    m_latest_frame_work_time = GetCurrentTimeInNanoseconds() - m_current_frame_start_work_time;
}

int64_t TimerSubsystem::GetCurrentTimeInNanoseconds()
{
    int64_t ticks;
    SDL_GetCurrentTime(&ticks);
    return ticks;
}
