#define VAMPTEST_MAIN
#include <vamptest/vamptest.h>

VAMP_DECLARE(MemoryDebugger, CreateMemoryDebugger);
VAMP_DECLARE(MemoryDebugger, AllocateOneMemory);
VAMP_DECLARE(MemoryDebugger, MultipleAllocations);
VAMP_DECLARE(MemoryDebugger, CheckListIntegrity);

void vampUserEntryPoint(VampTestApp *app)
{
    VAMP_REGISTER(app, MemoryDebugger, CreateMemoryDebugger);
    VAMP_REGISTER(app, MemoryDebugger, AllocateOneMemory);
    VAMP_REGISTER(app, MemoryDebugger, MultipleAllocations);
    VAMP_REGISTER(app, MemoryDebugger, CheckListIntegrity);
}
