#pragma once
#include "string.h"

class BitforgeInstance;

class Subsystem
{
public:
    Subsystem() = delete;
    explicit Subsystem(const String& subsystem_name, BitforgeInstance* engine_instance) : m_engine_instance(engine_instance), m_subsystem_name(subsystem_name) { BIT_LOG_INFO("Subsystem initializing: {}", m_subsystem_name.GetCString()); }
    virtual ~Subsystem() { BIT_LOG_INFO("Subsystem shutdown: {}", m_subsystem_name.GetCString()); }

    virtual bool ShouldTick() = 0;
    virtual void Tick(const int64_t delta_time_ns) { }

protected:
    BitforgeInstance* m_engine_instance = nullptr;
    String m_subsystem_name;
};
