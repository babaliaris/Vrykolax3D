#include <vrykolax3D/vrykolax3D.h>

int main()
{
    VX3D_TRACE("Hello Vrykolax3D");
    VX3D_INFO("Hello Vrykolax3D");
    VX3D_WARN("Hello Vrykolax3D");
    VX3D_ERROR("Hello Vrykolax3D");
    VX3D_FATAL("Hello Vrykolax3D");

    VX3D_COND(1==1, VX3D_WARN("Something when %s", "WRONG!"))

    VX3D_ASSERT(0==1)
    return 0;
}
