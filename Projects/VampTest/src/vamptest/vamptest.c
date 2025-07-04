#include "vamptest.h"
#include <vrykolax3D/core/vx3d_std.h>
#include <vrykolax3D/core/debug/vx3d_logger.h>
#include <vrykolax3D/core/debug/vx3d_assert.h>

VampTestNode *vampCreateTest(const char *suite_name, const char *test_name)
{
    VX3D_ASSERT(vx3D_strlen(suite_name) > VAMPTEST_MAX_NAME_CHARACTERS - 1);

    VampTestNode *new_test = (VampTestNode *)vx3D_malloc(VX3D_SIZEOF(VampTestNode));

    if (!new_test)
    {
        VX3D_WARN("Out of memory.");
        return NULL;
    }


}


void vampDestroyTest(VampTestNode **user_ptr)
{

}


VampTestApp *vampCreateApp()
{

}


void vampDestroyApp(VampTestApp **user_ptr)
{

}
