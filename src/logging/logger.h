#pragma once

#include "core/thread.h"
#include "core/uniqueptr.h"

class LoggingThread : public Thread
{
public:
    LoggingThread() : Thread("Logging Thread") { }
    int32_t Main() override;
};

class Logger
{
public:
    Logger() = default;
    static Logger* Get()
    {
        static Logger logger;
        return &logger;
    }

    void LogMessage();

private:
    LoggingThread m_logging_thread;
};
