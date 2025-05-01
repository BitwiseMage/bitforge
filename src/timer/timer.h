#pragma once
#include "core/subsystem.h"

class TimerSubsystem : public Subsystem
{
public:
    TimerSubsystem() = delete;
    explicit TimerSubsystem(BitforgeInstance* engine_instance) : Subsystem(String("Timer Subsystem"), engine_instance) { }
    bool ShouldTick() override { return true; }

    void SetMinimumFrameTime(const float minimum_frame_time_ms) { m_minimum_frame_time = static_cast<int64_t>(minimum_frame_time_ms * 1'000'000); }
    void MarkStartWork() { BIT_TRACING; m_current_frame_start_work_time = GetCurrentTimeInNanoseconds(); }
    void MarkEndWork() { BIT_TRACING; m_latest_frame_work_time = GetCurrentTimeInNanoseconds() - m_current_frame_start_work_time; }
    void PossibleSleep() const { BIT_TRACING; if (!m_minimum_frame_time) { return; } while (GetCurrentTimeInNanoseconds() - m_current_frame_start_work_time < m_minimum_frame_time); }

private:
    static int64_t GetCurrentTimeInNanoseconds();

    int64_t m_minimum_frame_time = 0;
    int64_t m_current_frame_start_work_time = 0;
    int64_t m_latest_frame_work_time = 0;
};