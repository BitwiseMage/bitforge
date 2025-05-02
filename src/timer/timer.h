#pragma once
#include "core/subsystem.h"

class TimerSubsystem : public Subsystem
{
public:
    TimerSubsystem() = delete;
    explicit TimerSubsystem(BitforgeInstance* engine_instance) : Subsystem(String("Timer Subsystem"), engine_instance) { }
    bool ShouldTick() override { return false; }

    void SetMinimumFrameTime(const float minimum_frame_time_ms) { m_minimum_frame_time = static_cast<int64_t>(minimum_frame_time_ms * 1'000'000); }
    void MarkStartWork();
    void MarkEndWork();
    void PossibleSleep() const;
    void FrameFinished();

    int64_t GetLatestFrameDeltaTimeNs() const { return m_latest_frame_work_time; }

private:
    static int64_t GetCurrentTimeInNanoseconds();

    int64_t m_minimum_frame_time = 0;
    int64_t m_current_frame_start_work_time = 0;
    int64_t m_latest_frame_work_time = 0;
};