#ifndef VX3D_MEM_DEBUG_H
#define VX3D_MEM_DEBUG_H

#include <vrykolax3D/core/vx3d_std.h>

#define VX3D_MEM_MAGIC_NUM 0xB10CB10CB10CB10C //BLOCK BLOCK BLOCK BLOCK
#define VX3D_MEM_BLOCK_DEAD 0xDEDEDEDEDEDEDEDE
#define VX3D_MEM_MAX_STR 256

typedef struct vx3DMemoryHeader
{
    VX3D_INT64  m_magic;
    VX3D_SIZE_T m_user_size;
    char        m_filename[VX3D_MEM_MAX_STR];
    int         m_line;

    struct vx3DMemoryHeader *m_next;
    struct vx3DMemoryHeader *m_prev;
}vx3DMemoryHeader;


typedef struct vx3DMemoryFooter
{
    VX3D_INT64  m_magic;
}vx3DMemoryFooter;


typedef struct vx3DMemoryDebugger
{
    VX3D_SIZE_T         m_allocations;
    vx3DMemoryHeader   *m_head;
    vx3DMemoryHeader   *m_tail;

    void *(*debug_malloc)(
        struct vx3DMemoryDebugger *self,
        VX3D_SIZE_T user_size,
        const char * filename,
        int line
    );

    void (*debug_free)(struct vx3DMemoryDebugger *self, void **user_ptr);

    char (*checkForLeaks)(struct vx3DMemoryDebugger *self);

    void (*reportLeaks)(struct vx3DMemoryDebugger *self);
}vx3DMemoryDebugger;


VX3D_EXTERN_C VX3D_API vx3DMemoryDebugger *vx3dCreateMemoryDebugger();

VX3D_EXTERN_C VX3D_API void vx3dDestroyMemoryDebugger(vx3DMemoryDebugger **mem_debugger);

#endif
