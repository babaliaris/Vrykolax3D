#ifndef VX3D_VRYKOLAX3D_H
#define VX3D_VRYKOLAX3D_H

#include <vrykolax3D/core/debug/vx3d_logger.h>
#include <vrykolax3D/core/debug/vx3d_assert.h>

int main()
{
    VX3D_TRACE("Hello Vrykolax3D");
    VX3D_INFO("Hello Vrykolax3D");
    VX3D_WARN("Hello Vrykolax3D");
    VX3D_ERROR("Hello Vrykolax3D");
    VX3D_FATAL("Hello Vrykolax3D");

    VX3D_COND(1==1, VX3D_WARN("Something when %s", "WRONG!"))

    VX3D_ASSERT(0==1, "0 is not equal to 1")
    return 0;
}

#endif
