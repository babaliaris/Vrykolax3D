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


static void *memStackPushImpl(void *src, VX3D_SIZE_T size)
{
    return NULL;
}


vx3DMemStack *vx3dCreateMemStack(VX3D_SIZE_T size)
{
    VX3D_ASSERT(size > 0);

    vx3DMemStack *new_stack = (vx3DMemStack *)VX3D_MALLOC(VX3D_SIZEOF(vx3DMemStack));

    if (!new_stack)
    {
        VX3D_WARN("Out of memory.");
        return NULL;
    }

    new_stack->m_buffer = VX3D_MALLOC(size);
    new_stack->push     = memStackPushImpl;

}


void vx3dDestroyMemStack(vx3DMemStack **stack)
{
    if (!stack || !(*stack))
    {
        VX3D_WARN("Function called with a NULL parameter.");
        return;
    }

    VX3D_FREE((*stack)->m_buffer);

    VX3D_FREE(*stack);
}
