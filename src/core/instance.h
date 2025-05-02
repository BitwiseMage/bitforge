#pragma once

#include "timer/timer.h"

class BitforgeInstance
{
public:
    BitforgeInstance();

    void Tick();

    void ExitRequest(const int32_t exit_code = 0) { m_requested_exit_code = exit_code; m_requested_exit = true; }

    bool IsExitRequested() const { return m_requested_exit; }
    int32_t GetExitRequestCode() const { return m_requested_exit_code; }

private:
    void TickSubsystems();

    TimerSubsystem* m_timer_subsystem = nullptr;
    Vector<UniquePtr<Subsystem>> m_subsystems_vector = Vector<UniquePtr<Subsystem>>(2);

    bool m_requested_exit = false;
    int32_t m_requested_exit_code = 0;
};
