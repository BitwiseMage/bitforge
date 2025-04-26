#include "instance.h"

#include "quill/Backend.h"

#include "tracing.h"
#include "logging/logger.h"

BitforgeInstance::BitforgeInstance() = default;

void BitforgeInstance::Tick()
{
    BIT_TRACING;
}
