#include "logger.h"

#include "quill/Frontend.h"
#include "quill/Backend.h"
#include "quill/sinks/ConsoleSink.h"

Logger::Logger()
{
    quill::Backend::start();
    std::shared_ptr<quill::Sink> console_sink = quill::Frontend::create_or_get_sink<quill::ConsoleSink>("sink_console_0");
#ifdef NDEBUG
    quill::PatternFormatterOptions pattern_formatter_options("[%(time)] [%(log_level:<8)] %(message)");
#else
    quill::PatternFormatterOptions pattern_formatter_options("[%(time)] %(short_source_location:<20) [%(log_level:<8)] %(message)");
#endif

    m_logger = quill::Frontend::create_or_get_logger("root", std::move(console_sink), pattern_formatter_options);
    m_logger->set_log_level(quill::LogLevel::TraceL3);
}

Logger::~Logger()
{
    FLushLogs();
    quill::Backend::stop();
}

void Logger::FLushLogs() const
{
    m_logger->flush_log();
}
