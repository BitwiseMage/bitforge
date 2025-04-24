#include "core/instance.h"
#include "logging/logging.h"

int main()
{
    Bitforge::CoreInstance core_instance;
    while (!core_instance.IsExitRequested())
    {
        core_instance.Tick();
        BITFORGE_TRACING_FRAME_NAMED("main_loop");
    }

    return 0;
}