#ifndef VX3D_MEM_DEBUG_H
#define VX3D_MEM_DEBUG_H
#include <vrykolax3D/core/vx3d_std.h>

/**
 * @file
 * @brief Tools for memory allocation debugging.
 * @author Bampaliaris Nikolaos
 */

#define VX3D_MEM_MAGIC_NUM 0xB10CB10CB10CB10C
#define VX3D_MEM_BLOCK_DEAD 0xDEDEDEDEDEDEDEDE
#define VX3D_MEM_MAX_STR 256


/**
 * @brief Memory block header segment.
 * @private
 * 
 * This lives on top of the users memory segment, and
 * it's purposes is to store some metadata for 
 * identifing memory blocks in debug mode. It also tracks
 * the filename and the line where the allocation happened.
 */
typedef struct vx3DMemoryHeader
{
    VX3D_INT64  m_magic;
    VX3D_SIZE_T m_user_size;
    char        m_filename[VX3D_MEM_MAX_STR];
    int         m_line;

    struct vx3DMemoryHeader *m_next;
    struct vx3DMemoryHeader *m_prev;
}vx3DMemoryHeader;



/**
 * @brief Memory block footer segment.
 * @private
 * 
 * It is used for detecting overflows.
 */
typedef struct vx3DMemoryFooter
{
    VX3D_INT64  m_magic;
}vx3DMemoryFooter;


/**
 * @brief A double linked list that tracks allocations and general memory safety.
 * @private
 * 
 * Each node of the list is a memory block with the following structure:
 * { header_segment | user_segment | footer_segment }. 
 * The functions vx3DMemoryDebugger SHOULD not be called directly, but instead 
 * you should use the macros VX3D_MALLOC() & VX3D_FREE() that will strip
 * this debugging functionality in release and dist builds.
 */
typedef struct vx3DMemoryDebugger
{
    VX3D_SIZE_T         m_allocations;
    vx3DMemoryHeader   *m_head;
    vx3DMemoryHeader   *m_tail;

    /**
     * @brief Allocates memory in the HEAP.
     * 
     * Uses the default OS memory strategy (classic malloc) to 
     * allocate the debuggable memory block 
     * { header_segment | user_segment | footer_segment }.
     * The user segment is initialized with 0.
     * 
     * @param[in] self The vx3DMemoryDebugger object.
     * @param[in] user_size The size (in bytes) of the desired allocation.
     * @param[in] filename The filename of where this allocation happened.
     * @param[in] line The line of where this allocation happened.
     * 
     * @returns The memory address of the user segment.
     */
    void *(*debug_malloc)(
        struct vx3DMemoryDebugger *self,
        VX3D_SIZE_T user_size,
        const char * filename,
        int line
    );

    /**
     * @brief Frees a memory block.
     * 
     * Uses the default OS memory strategy (classic free) but also
     * checks for underflows or overflows and other memory related safety.
     * The whole memory block is deinitialized with the value VX3D_MEM_BLOCK_DEAD .
     * 
     * @param[in] self The vx3DMemoryDebugger object.
     * @param[in,out] user_ptr The user pointer that holds the address of the user_segment. We set it to null after freeing the memory.
     */
    void (*debug_free)(struct vx3DMemoryDebugger *self, void **user_ptr);


    /**
     * @brief Check if there are memory leaks.
     * 
     * You should call this method BEFORE the termination of the entire
     * application. If the number of mallocs and frees is not the same, 
     * this function will return 1 -> memory leaks.
     * 
     * @param[in] self The vx3DMemoryDebugger object.
     * 
     * @return 1 If there are currently allocated blocks, 0 otherwise.
     */
    char (*checkForLeaks)(struct vx3DMemoryDebugger *self);


    /**
     * @brief Logs any memory leaks.
     * 
     * You should call this method BEFORE the termination of the application!
     * If the number of mallocs and frees is not the same, this method
     * will look through the allocation tracking list and report all the remaining
     * allocations in the current selected logging output.
     */
    void (*reportLeaks)(struct vx3DMemoryDebugger *self);

}vx3DMemoryDebugger;



/**
 * @brief Creates a new vx3DMemoryDebugger object.
 * 
 * @returns The newly created vx3DMemoryDebugger object.
 */
VX3D_EXTERN_C VX3D_API vx3DMemoryDebugger *vx3dCreateMemoryDebugger();


/**
 * @brief Destroys a vx3DMemoryDebugger object.
 * 
 * @param[in,out] mem_debugger The user address of the vx3DMemoryDebugger object. We set it to null after freeing the memory.
 */
VX3D_EXTERN_C VX3D_API void vx3dDestroyMemoryDebugger(vx3DMemoryDebugger **mem_debugger);

#endif
