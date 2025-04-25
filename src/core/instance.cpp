#include "instance.h"

#include "tracing.h"
#include "logging/logger.h"

BitforgeInstance::BitforgeInstance() = default;

void BitforgeInstance::Tick() { BITFORGE_TRACING; }
