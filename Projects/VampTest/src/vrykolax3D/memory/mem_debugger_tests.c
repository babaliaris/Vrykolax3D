#include <vamptest/vamptest.h>
#include <vrykolax3D/core/debug/vx3d_mem_debug.h>

VAMP_TEST(MemoryDebugger, CreateMemoryDebugger)
{
    vx3DMemoryDebugger *debugger = vx3dCreateMemoryDebugger();

    VAMP_ASSERT(debugger->m_head == NULL);
    VAMP_ASSERT(debugger->m_tail == NULL);
    VAMP_ASSERT(debugger->m_allocations == 0);
    VAMP_ASSERT(debugger->debug_malloc != NULL);
    VAMP_ASSERT(debugger->debug_free != NULL);
    VAMP_ASSERT(debugger->checkForLeaks != NULL);
    VAMP_ASSERT(debugger->reportLeaks != NULL);

    vx3dDestroyMemoryDebugger(&debugger);

    VAMP_ASSERT(debugger == NULL);
}



VAMP_TEST(MemoryDebugger, AllocateOneMemory)
{
    vx3DMemoryDebugger *debugger = vx3dCreateMemoryDebugger();

    int  mem1_value = 10245;
    int *mem1       = (int *)debugger->debug_malloc(debugger, VX3D_SIZEOF(int), __FILE__, __LINE__);
    vx3D_memcpy( mem1, &mem1_value, VX3D_SIZEOF(int) );

    VAMP_ASSERT(mem1_value == *mem1);
    VAMP_ASSERT(debugger->m_head == debugger->m_tail);
    VAMP_ASSERT(debugger->m_allocations == 1);
    VAMP_ASSERT(debugger->checkForLeaks(debugger) == 1);

    debugger->debug_free(debugger, (void **)&mem1);

    VAMP_ASSERT(debugger->m_head == NULL);
    VAMP_ASSERT(debugger->m_tail == NULL);
    VAMP_ASSERT(debugger->m_allocations == 0);
    VAMP_ASSERT(debugger->checkForLeaks(debugger) == 0);

    vx3dDestroyMemoryDebugger(&debugger);
    VAMP_ASSERT(debugger == NULL);
}


VAMP_TEST(MemoryDebugger, MultipleAllocations)
{
    vx3DMemoryDebugger *debugger = vx3dCreateMemoryDebugger();

    //Allocate an integer.
    int  mem1_value = 10245;
    int *mem1       = (int *)debugger->debug_malloc(debugger, VX3D_SIZEOF(int), __FILE__, __LINE__);
    vx3D_memcpy( mem1, &mem1_value, VX3D_SIZEOF(int) );

    //Allocate a floating number.
    float  mem2_value = 3.1415f;
    float *mem2       = (float *)debugger->debug_malloc(debugger, VX3D_SIZEOF(float), __FILE__, __LINE__);
    vx3D_memcpy( mem2, &mem2_value, VX3D_SIZEOF(float) );

    //Allocate a double number.
    double  mem3_value = 3.14159265f;
    double *mem3       = (double *)debugger->debug_malloc(debugger, VX3D_SIZEOF(double), __FILE__, __LINE__);
    vx3D_memcpy( mem3, &mem3_value, VX3D_SIZEOF(double) );

    //Check the values of the allocations.
    VAMP_ASSERT(mem1_value == *mem1);
    VAMP_ASSERT(mem2_value == *mem2);
    VAMP_ASSERT(mem3_value == *mem3);

    //Check the state of the debugger.
    VAMP_ASSERT(debugger->m_head != NULL);
    VAMP_ASSERT(debugger->m_tail != NULL);
    VAMP_ASSERT(debugger->m_allocations == 3);
    VAMP_ASSERT(debugger->checkForLeaks(debugger) == 1);

    //Free the allocations.
    debugger->debug_free(debugger, (void **)&mem1);
    debugger->debug_free(debugger, (void **)&mem2);
    debugger->debug_free(debugger, (void **)&mem3);

    //Check the state of the debugger.
    VAMP_ASSERT(debugger->m_head == NULL);
    VAMP_ASSERT(debugger->m_tail == NULL);
    VAMP_ASSERT(debugger->m_allocations == 0);
    VAMP_ASSERT(debugger->checkForLeaks(debugger) == 0);

    vx3dDestroyMemoryDebugger(&debugger);
    VAMP_ASSERT(debugger == NULL);
}


VAMP_TEST(MemoryDebugger, CheckListIntegrity)
{
    vx3DMemoryDebugger *debugger = vx3dCreateMemoryDebugger();

    //Allocate an integer.
    int  mem1_value = 10245;
    int *mem1       = (int *)debugger->debug_malloc(debugger, VX3D_SIZEOF(int), __FILE__, __LINE__);
    vx3D_memcpy( mem1, &mem1_value, VX3D_SIZEOF(int) );

    //Allocate a floating number.
    int  mem2_value = 108;
    int *mem2       = (int *)debugger->debug_malloc(debugger, VX3D_SIZEOF(int), __FILE__, __LINE__);
    vx3D_memcpy( mem2, &mem2_value, VX3D_SIZEOF(int) );


    //Allocate a double number.
    int  mem3_value = 1996;
    int *mem3       = (int *)debugger->debug_malloc(debugger, VX3D_SIZEOF(int), __FILE__, __LINE__);
    vx3D_memcpy( mem3, &mem3_value, VX3D_SIZEOF(int) );

    //Check the values of the allocations.
    VAMP_ASSERT(mem1_value == *mem1);
    VAMP_ASSERT(mem2_value == *mem2);
    VAMP_ASSERT(mem3_value == *mem3);

    //Check the state of the debugger.
    VAMP_ASSERT(debugger->m_head != NULL);
    VAMP_ASSERT(debugger->m_tail != NULL);
    VAMP_ASSERT(debugger->m_allocations == 3);
    VAMP_ASSERT(debugger->checkForLeaks(debugger) == 1);

    //Go though all the memory allocations and check the memory.
    VX3D_SIZE_T i = 0;
    int values[3] = {mem1_value, mem2_value, mem3_value};
    vx3DMemoryHeader *currentBlock = debugger->m_head;
    while (currentBlock)
    {
        //Check footer metadata..
        VAMP_ASSERT(currentBlock->m_magic == VX3D_MEM_MAGIC_NUM);
        VAMP_ASSERT(currentBlock->m_line > -1);
        VAMP_ASSERT( vx3D_strcmp(currentBlock->m_filename, __FILE__) == 0 );
        VAMP_ASSERT(currentBlock->m_user_size == VX3D_SIZEOF(int) );

        //Check user data.
        int *user_ptr = (int *)( (char *)currentBlock + VX3D_SIZEOF(vx3DMemoryHeader) );
        VAMP_ASSERT(*user_ptr == values[i]);

        //Check footer.
        vx3DMemoryFooter *footer_ptr = (vx3DMemoryFooter *)( (char *)user_ptr + currentBlock->m_user_size );
        VAMP_ASSERT(footer_ptr->m_magic == VX3D_MEM_MAGIC_NUM);

        //Go to the next mem block and value.
        currentBlock = currentBlock->m_next;
        i++;
    }

    //Free the allocations.
    debugger->debug_free(debugger, (void **)&mem1);
    debugger->debug_free(debugger, (void **)&mem2);
    debugger->debug_free(debugger, (void **)&mem3);

    //Check the state of the debugger.
    VAMP_ASSERT(debugger->m_head == NULL);
    VAMP_ASSERT(debugger->m_tail == NULL);
    VAMP_ASSERT(debugger->m_allocations == 0);
    VAMP_ASSERT(debugger->checkForLeaks(debugger) == 0);

    vx3dDestroyMemoryDebugger(&debugger);
    VAMP_ASSERT(debugger == NULL);
}
