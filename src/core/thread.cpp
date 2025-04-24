#include "thread.h"

#include <SDL3/SDL_thread.h>

#include "core/tracing.h"

static int SdlThreadFunc(void* data)
{
    Thread* thread = static_cast<Thread*>(data);
    // log thread starting
    int exit_code = thread->Main();
    // log thread exiting
    return exit_code;
}


Thread::Thread(const char* thread_name)
{
    BITFORGE_TRACING;

    SDL_Thread* thread = SDL_CreateThread(SdlThreadFunc, thread_name, this);
    if (!thread)
    {
        return;
    }

    m_thread_created = true;
    m_thread = thread;
}

bool Thread::Join() const
{
    if (!m_thread || !m_thread_created)
    {
        return false;
    }

    SDL_WaitThread(m_thread, nullptr);
    return true;
}
