#include "logger.h"

#include "quill/Frontend.h"
#include "quill/Backend.h"
#include "quill/sinks/ConsoleSink.h"

Logger::Logger()
{
    quill::BackendOptions backend_options;
    quill::Backend::start(backend_options);

    std::shared_ptr<quill::Sink> console_sink = quill::Frontend::create_or_get_sink<quill::ConsoleSink>("sink_console_0");
#if !NDEBUG
    quill::PatternFormatterOptions pattern_formatter_options("[%(time)] [%(log_level:<8)] %(message)");
#else
    quill::PatternFormatterOptions pattern_formatter_options("[%(time)] %(short_source_location:<28) [%(log_level:<8)] %(message)");
#endif

    m_logger.Acquire(quill::Frontend::create_or_get_logger("root", std::move(console_sink), pattern_formatter_options));
    m_logger->set_log_level(quill::LogLevel::TraceL3);
}
