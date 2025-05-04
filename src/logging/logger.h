#pragma once

#include "core/uniqueptr.h"
#include "quill/Logger.h"
#include "quill/LogMacros.h"

#define BIT_LOG_TRACE3(fmt, ...) QUILL_LOG_TRACE_L3(Logger::Get()->GetMainLoggerPtr(), fmt, __VA_ARGS__)
#define BIT_LOG_TRACE2(fmt, ...) QUILL_LOG_TRACE_L2(Logger::Get()->GetMainLoggerPtr(), fmt, __VA_ARGS__)
#define BIT_LOG_TRACE(fmt, ...) QUILL_LOG_TRACE_L1(Logger::Get()->GetMainLoggerPtr(), fmt, __VA_ARGS__)
#define BIT_LOG_DEBUG(fmt, ...) QUILL_LOG_DEBUG(Logger::Get()->GetMainLoggerPtr(), fmt, __VA_ARGS__)
#define BIT_LOG_INFO(fmt, ...) QUILL_LOG_INFO(Logger::Get()->GetMainLoggerPtr(), fmt, __VA_ARGS__)
#define BIT_LOG_WARNING(fmt, ...) QUILL_LOG_WARNING(Logger::Get()->GetMainLoggerPtr(), fmt, __VA_ARGS__)
#define BIT_LOG_ERROR(fmt, ...) QUILL_LOG_ERROR(Logger::Get()->GetMainLoggerPtr(), fmt, __VA_ARGS__)
#define BIT_LOG_CRITICAL(fmt, ...) QUILL_LOG_CRITICAL(Logger::Get()->GetMainLoggerPtr(), fmt, __VA_ARGS__)

class Logger
{
public:
    Logger();
    ~Logger();

    static Logger* Get()
    {
        static Logger logger;
        return &logger;
    }

    quill::Logger* GetMainLoggerPtr() const { return m_logger; }
    void FLushLogs() const;

private:
    quill::Logger* m_logger;
};
