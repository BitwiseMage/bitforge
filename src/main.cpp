#include "core/engineinstance.h"
#include "core/logging.h"
#include "core/memory.h"

int main()
{
    Bitforge::EngineInstance engine_instance;
    while (!engine_instance.IsExitRequested())
    {
        engine_instance.Tick();
        BITFORGE_TRACING_FRAME_NAMED("main_loop");
    }

    return 0;
}