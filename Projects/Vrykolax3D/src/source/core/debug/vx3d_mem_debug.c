#include <vrykolax3D/core/debug/vx3d_mem_debug.h>
#include <vrykolax3D/core/debug/vx3d_logger.h>
#include <vrykolax3D/core/debug/vx3d_assert.h>

static void *mallocImpl(
    vx3DMemoryDebugger *self,
    VX3D_SIZE_T user_size,
    const char * filename,
    int line
)
{
    //Fatal assertions persist in all builds!!!
    VX3D_FATAL_ASSERT(self != NULL);
    VX3D_FATAL_ASSERT( vx3D_strlen(filename) < VX3D_MEM_MAX_STR );
    VX3D_FATAL_ASSERT(user_size > 0 && line >-1);

    //Allocate enough memory.
    char *new_block  = (char *)vx3D_malloc( VX3D_SIZEOF(vx3DMemoryHeader) + user_size + VX3D_SIZEOF(vx3DMemoryFooter) );

    //Calculate intermediate pointers.
    vx3DMemoryHeader *header_ptr = (vx3DMemoryHeader *)new_block;
    vx3DMemoryFooter *footer_ptr = (vx3DMemoryFooter *)(new_block + VX3D_SIZEOF(vx3DMemoryHeader) + user_size );
    void *user_ptr               = (void *)(new_block + VX3D_SIZEOF(vx3DMemoryHeader) );

    //Initialize Header.
    header_ptr->m_magic     = VX3D_MEM_MAGIC_NUM;
    header_ptr->m_user_size = user_size;
    header_ptr->m_line      = line;
    header_ptr->m_next      = NULL;
    header_ptr->m_prev      = NULL;
    vx3D_strncpy(header_ptr->m_filename, filename, VX3D_MEM_MAX_STR);
    header_ptr->m_filename[VX3D_MEM_MAX_STR - 1] = '\0';

    //Initialize Footer.
    footer_ptr->m_magic     = VX3D_MEM_MAGIC_NUM;

    //ZERO the user memory.
    vx3D_memset(user_ptr, 0, user_size);

    //The allocations track list is empty.
    if (self->m_head == NULL && self->m_tail == NULL)
    {
        //header_ptr ALWAYS points at the start of the memory block.
        self->m_head = header_ptr;
        self->m_tail = header_ptr;
    }

    //Append it at the end of the list.
    else
    {
        //Check for incomplete list. This should NEVER happen.
        VX3D_FATAL_ASSERT(self->m_head != NULL && self->m_tail != NULL);

        //Make the connection.
        self->m_tail->m_next    = header_ptr;
        header_ptr->m_prev      = self->m_tail;
        self->m_tail            = header_ptr;
    }

    //Increase the number of allocations.
    self->m_allocations++;

    return user_ptr;
}


static void freeImpl(vx3DMemoryDebugger *self, void **user_ptr)
{
    VX3D_FATAL_ASSERT(self != NULL);
    VX3D_FATAL_ASSERT((*user_ptr) != NULL);

    //Calculate the start address of the mem block.
    vx3DMemoryHeader *header_ptr = (vx3DMemoryHeader *)( (char *)(*user_ptr) - VX3D_SIZEOF(vx3DMemoryHeader));

    //Calculate the footer address.
    vx3DMemoryFooter *footer_ptr = (vx3DMemoryFooter *)( (char *)(*user_ptr) + header_ptr->m_user_size );

    VX3D_FATAL_ASSERT(header_ptr->m_magic != VX3D_MEM_BLOCK_DEAD); //This memory has already be freed.
    VX3D_FATAL_ASSERT(header_ptr->m_magic == VX3D_MEM_MAGIC_NUM); //Underflow detected or not a MEM block.
    VX3D_FATAL_ASSERT(footer_ptr->m_magic == VX3D_MEM_MAGIC_NUM); //Overflow detected.

    //Since we try to delete a memory block, THERE MUST be at least ONE.
    VX3D_FATAL_ASSERT(self->m_head != NULL && self->m_tail != NULL && self->m_allocations > 0);

    //There is only one node in the list.
    if (self->m_head == self->m_tail)
    {
        VX3D_ASSERT(self->m_head == header_ptr && self->m_allocations == 1);

        self->m_head = NULL;
        self->m_tail = NULL;
    }

    //We try to remove the HEAD of the list.
    else if (header_ptr == self->m_head)
    {
        self->m_head            = self->m_head->m_next;
        self->m_head->m_prev    = NULL;
    }

    //We try to remove the TAIL of the list.
    else if (header_ptr == self->m_tail)
    {
        self->m_tail            = self->m_tail->m_prev;
        self->m_tail->m_next    = NULL;
    }

    //Intermediate node.
    else
    {
        header_ptr->m_prev->m_next = header_ptr->m_next;
        header_ptr->m_next->m_prev = header_ptr->m_prev;
    }

    //Set the entire memory to the repeating value of 0xDE (for example 0xDEDEDEDEDEDEDEDE)
    vx3D_memset((void *)header_ptr, 0xDE, VX3D_SIZEOF(vx3DMemoryHeader) + header_ptr->m_user_size + VX3D_SIZEOF(vx3DMemoryFooter));

    //Free the memory block.
    vx3D_free((void *)header_ptr);

    /*Set the user pointer to NULL.
        This prevents him of accidentally writting
        to a freed memory. If he tries to do so,
        he will get a segmentation fault.
    */
    *user_ptr = NULL;

    //Decrease the number of allocations.
    self->m_allocations--;
}


static char checkForLeaksImpl(vx3DMemoryDebugger *self)
{
    VX3D_FATAL_ASSERT(self != NULL);
    return self->m_allocations > 0;
}



static void reportLeaksImpl(vx3DMemoryDebugger *self)
{
    VX3D_FATAL_ASSERT(self != NULL);

    vx3DMemoryHeader *current = self->m_head;

    while (current)
    {
        //TODO Later enable file logging.
        VX3D_COLORFUL_LOG_MEM_LEAK(
            VX3D_ANSI_FATAL,
            "MEMORY LEAK",
            "vx3DMemoryDebugger",
            current->m_filename,
            current->m_line,
            current->m_user_size
        );

        current = current->m_next;
    }
}


vx3DMemoryDebugger *vx3dCreateMemoryDebugger()
{
    vx3DMemoryDebugger *new_debugger = (vx3DMemoryDebugger *)vx3D_malloc(VX3D_SIZEOF(vx3DMemoryDebugger));

    if (!new_debugger)
    {
        VX3D_WARN("Out of memory.");
        return NULL;
    }

    new_debugger->m_allocations = 0;
    new_debugger->m_head        = NULL;
    new_debugger->m_tail        = NULL;
    new_debugger->debug_malloc  = mallocImpl;
    new_debugger->debug_free    = freeImpl;
    new_debugger->checkForLeaks = checkForLeaksImpl;
    new_debugger->reportLeaks   = reportLeaksImpl;

    return new_debugger;
}


void vx3dDestroyMemoryDebugger(vx3DMemoryDebugger **mem_debugger)
{
    //Check the function parameter.
    if (mem_debugger == NULL || (*mem_debugger) == NULL)
    {
        VX3D_WARN("Destroy function called with a NULL parameter.");
        return;
    }

    //Clean up for the user.
    vx3DMemoryHeader *current = (*mem_debugger)->m_head;
    vx3DMemoryHeader *temp;
    void *user_ptr;
    while (current)
    {
        temp     = current;
        current  = current->m_next;
        user_ptr = (void *)( (char *)temp + VX3D_SIZEOF(vx3DMemoryHeader) );

        //Free the memory block.
        (*mem_debugger)->debug_free(*mem_debugger, &user_ptr );
    }

    vx3D_free(*mem_debugger);

    *mem_debugger = NULL;
}
