#include "instance.h"

#include "quill/Backend.h"

#include "tracing.h"
#include "logging/logger.h"

BitforgeInstance::BitforgeInstance()
{
    m_timer_subsystem.SetMinimumFrameTime(16.6f);
}

void BitforgeInstance::Tick()
{
    BIT_TRACING;

    m_timer_subsystem.MarkStartWork();
    // Work fits here
    m_timer_subsystem.MarkEndWork();
    m_timer_subsystem.PossibleSleep();
}
