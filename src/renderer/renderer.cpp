#include "renderer.h"

#include "core/instance.h"

RendererSubsystem::RendererSubsystem(BitforgeInstance* engine_instance) : Subsystem(String("Renderer Subsystem"), engine_instance)
{

}

RendererSubsystem::~RendererSubsystem()
{

}

void RendererSubsystem::Tick(const int64_t delta_time_ns)
{
    BIT_TRACING;
    m_engine_instance->ExitRequest(0);
}
