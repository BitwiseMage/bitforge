#pragma once

#include <cstdint>

class BitforgeInstance
{
public:
    BitforgeInstance();

    void Tick();

    void ExitRequest(const int32_t exit_code = 0) { m_requested_exit_code = exit_code; m_requested_exit = true; }

    bool IsExitRequested() const { return m_requested_exit; }
    int32_t GetExitRequestCode() const { return m_requested_exit_code; }

private:
    bool m_requested_exit = false;
    int32_t m_requested_exit_code = 0;
};
