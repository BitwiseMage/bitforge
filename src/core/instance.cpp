#include "instance.h"

#include "tracing.h"

#include "renderer/renderer.h"

BitforgeInstance::BitforgeInstance()
{
    UniquePtr<TimerSubsystem> timer_subsystem = MakeUniquePtr<TimerSubsystem>(this);
    m_timer_subsystem = timer_subsystem.GetRawPtr();
    m_timer_subsystem->SetMinimumFrameTime(16.6666f);

    m_subsystems_vector.PushBack(static_cast<UniquePtr<Subsystem>>(std::move(timer_subsystem)));
    m_subsystems_vector.PushBack(static_cast<UniquePtr<Subsystem>>(MakeUniquePtr<RendererSubsystem>(this)));
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
    BIT_TRACING;
    const int64_t delta_time_ns = m_timer_subsystem->GetLatestFrameDeltaTimeNs();
    for (const UniquePtr<Subsystem>& subsystem: m_subsystems_vector)
    {
        if (!subsystem->ShouldTick())
        {
            continue;
        }

        subsystem->Tick(delta_time_ns);
    }
}
