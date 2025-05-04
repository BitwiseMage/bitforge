#include "thread.h"

#include <SDL3/SDL_thread.h>

#include "core/tracing.h"
#include "logging/logger.h"

static int SdlThreadFunc(void* data)
{
    Thread* thread = static_cast<Thread*>(data);
    BIT_LOG_INFO("Starting thread");
    int exit_code = thread->Main();
    BIT_LOG_INFO("Exiting thread with code {}", exit_code);
    return exit_code;
}

Thread::Thread(const char* thread_name)
{
    BIT_TRACING;

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
    BIT_TRACING;

    if (!m_thread || !m_thread_created)
    {
        return false;
    }

    {
        BIT_TRACING_NAMED("Thread::Join::SDL_WaitThread");
        SDL_WaitThread(m_thread, nullptr);
    }
    return true;
}
