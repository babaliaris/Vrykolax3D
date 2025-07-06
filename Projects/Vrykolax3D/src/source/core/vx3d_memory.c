#include <vrykolax3D/core/vx3d_memory.h>
#include <vrykolax3D/core/debug/vx3d_logger.h>
#include <vrykolax3D/core/debug/vx3d_assert.h>

//Initialize the memory debugger in DEBUG mode.
#ifdef VX3D_DEBUG_ON
    vx3DMemoryDebugger *VX3D_GLOBAL_MEM_DEBUGGER = NULL;
#endif


char vx3dMemoryInit()
{
    //Create the memory debugger in DEBUG mode.
    #ifdef VX3D_DEBUG_ON
        VX3D_GLOBAL_MEM_DEBUGGER = vx3dCreateMemoryDebugger();
        return VX3D_GLOBAL_MEM_DEBUGGER != NULL;
    #endif

    return 1;
}



void vx3dMemoryDeinit()
{   
    //Destroy the memory debugger in DEBUG mode.
    #ifdef VX3D_DEBUG_ON
        VX3D_FATAL_ASSERT(VX3D_GLOBAL_MEM_DEBUGGER != NULL);
        vx3dDestroyMemoryDebugger(&VX3D_GLOBAL_MEM_DEBUGGER);
    #endif
}
