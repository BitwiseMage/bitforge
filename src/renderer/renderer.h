#pragma once

#include "core/subsystem.h"

class RendererSubsystem : public Subsystem
{
public:
    RendererSubsystem() = delete;
    explicit RendererSubsystem(BitforgeInstance* engine_instance);
    ~RendererSubsystem();

    bool ShouldTick() override { return true; }

    void Tick(const int64_t delta_time_ns) override;
};