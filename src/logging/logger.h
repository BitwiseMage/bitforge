#pragma once

#include "core/uniqueptr.h"

#define BIT_LOG_TRACE3(fmt, ...)  
#define BIT_LOG_TRACE2(fmt, ...)  
#define BIT_LOG_TRACE(fmt, ...)  
#define BIT_LOG_DEBUG(fmt, ...)  
#define BIT_LOG_INFO(fmt, ...)  
#define BIT_LOG_WARNING(fmt, ...)  
#define BIT_LOG_ERROR(fmt, ...)  
#define BIT_LOG_CRITICAL(fmt, ...)  

class Logger
{
public:
    Logger();
    static Logger* Get()
    {
        static Logger logger;
        return &logger;
    }

private:
};
