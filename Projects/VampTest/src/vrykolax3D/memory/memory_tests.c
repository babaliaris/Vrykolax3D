#include <vamptest/vamptest.h>
#include <vrykolax3D/core/vx3d_memory.h>

VAMP_TEST(Memory, MallocAndFree)
{
    vx3dMemoryInit();

    int *mem1   = (int *)VX3D_MALLOC(VX3D_SIZEOF(int));
    *mem1       = 1024;

    VAMP_ASSERT(mem1 != NULL);
    VAMP_ASSERT(*mem1 == 1024);

    VX3D_FREE(mem1);

    #ifdef VX3D_DEBUG_ON
        VAMP_ASSERT(mem1 == NULL);
    #endif

    vx3dMemoryDeinit();

    #ifdef VX3D_DEBUG_ON
        VAMP_ASSERT(VX3D_GLOBAL_MEM_DEBUGGER == NULL);
    #endif
}
