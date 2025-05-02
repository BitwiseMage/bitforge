#include "instance.h"

#include "quill/Backend.h"

#include "tracing.h"

BitforgeInstance::BitforgeInstance()
{

    UniquePtr<TimerSubsystem> timer_subsystem = MakeUniquePtr<TimerSubsystem>(this);
    m_timer_subsystem = timer_subsystem.GetRawPtr();
    m_timer_subsystem->SetMinimumFrameTime(16.6666f);

    m_subsystems_vector.PushBack(std::move(timer_subsystem));
}

void BitforgeInstance::Tick()
{
    BIT_TRACING;
    m_timer_subsystem->MarkStartWork();
    TickSubsystems();
    m_timer_subsystem->MarkEndWork();
}

void BitforgeInstance::TickSubsystems()
{
    for (const UniquePtr<Subsystem>& subsystem: m_subsystems_vector)
    {
        if (subsystem->ShouldTick())
        {
            subsystem->Tick();
        }
    }
}
