#include "core/instance.h"
#include "core/tracing.h"

int main()
{
    BitforgeInstance core_instance;
    while (!core_instance.IsExitRequested())
    {
        core_instance.Tick();
        BIT_TRACING_FRAME_NAMED("main_loop");
    }

    return 0;
}
