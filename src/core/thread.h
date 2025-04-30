#pragma once

#include <cstdint>

struct SDL_Thread;

class Thread
{
public:
    Thread() = delete;
    explicit Thread(const char* thread_name);
    virtual ~Thread() = default;

    virtual int32_t Main() = 0;
    bool Join() const;

private:
    SDL_Thread* m_thread = nullptr;
    bool m_thread_created = false;
    char* m_thread_name = nullptr;
};
