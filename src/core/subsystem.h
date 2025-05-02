#pragma once
#include "string.h"

class BitforgeInstance;

class Subsystem
{
public:
    Subsystem() = delete;
    explicit Subsystem(const String& subsystem_name, BitforgeInstance* engine_instance) : m_engine_instance(engine_instance), m_subsystem_name(subsystem_name) { }
    virtual ~Subsystem() = default;

    virtual bool ShouldTick() = 0;
    virtual void Tick(const int64_t delta_time_ns) { }

private:
    BitforgeInstance* m_engine_instance = nullptr;
    String m_subsystem_name;
};
