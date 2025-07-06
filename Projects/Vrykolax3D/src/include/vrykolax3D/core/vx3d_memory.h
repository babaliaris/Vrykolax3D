#ifndef VX3D_MEMORY_H
#define VX3D_MEMORY_H
#include <vrykolax3D/core/debug/vx3d_mem_debug.h>


/**
 * @file
 * @brief Memory related functionality.
 * @author Bampaliaris Nikolaos
 */


#ifdef VX3D_DEBUG_ON
    VX3D_EXTERN_C extern VX3D_API vx3DMemoryDebugger *VX3D_GLOBAL_MEM_DEBUGGER;
#endif

/**
 * @brief Initialize the memory unit.
 */
VX3D_EXTERN_C VX3D_API char vx3dMemoryInit();


/**
 * @brief Deinitialize the memory unit.
 */
VX3D_EXTERN_C VX3D_API void vx3dMemoryDeinit();


#ifdef VX3D_DEBUG_ON
    #define VX3D_MALLOC(size)\
        VX3D_GLOBAL_MEM_DEBUGGER->debug_malloc(VX3D_GLOBAL_MEM_DEBUGGER, size, __FILE__, __LINE__)

    #define VX3D_FREE(mem_var)\
        VX3D_GLOBAL_MEM_DEBUGGER->debug_free(VX3D_GLOBAL_MEM_DEBUGGER, (void **)&mem_var)

#else
    #define VX3D_MALLOC(size) vx3D_malloc(size)

    #define VX3D_FREE(mem_var) vx3D_free(mem_var)
#endif


typedef struct vx3DMemStack
{
    void *m_buffer;

    void *(*push)(void *src, VX3D_SIZE_T size);
}vx3DMemStack;


VX3D_EXTERN_C VX3D_API vx3DMemStack *vx3dCreateMemStack(VX3D_SIZE_T size);

VX3D_EXTERN_C VX3D_API void vx3dDestroyMemStack(vx3DMemStack **stack);

#endif