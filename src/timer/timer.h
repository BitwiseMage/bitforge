#pragma once
#include "core/subsystem.h"

class TimerSubsystem : public Subsystem
{
public:
    TimerSubsystem() = delete;
    explicit TimerSubsystem(BitforgeInstance* engine_instance) : Subsystem(String("Timer Subsystem"), engine_instance) { }
    bool ShouldTick() override { return true; }

    void MarkStartWork();
    void MarkEndWork();
    void PossibleSleep();

private:

};