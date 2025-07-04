#ifndef VX3D_ASSERT_H
#define VX3D_ASSERT_H
#include <vrykolax3D/core/debug/vx3d_logger.h>

#ifdef VX3D_DEBUG_ON
    #define VX3D_ASSERT(cond)\
        if ( !(cond) )\
        {\
            VX3D_COLORFUL_LOG_MSG(VX3D_ANSI_ERROR, "ASSERTION FAILED", "Vrykolax3D", __FILE__, __LINE__, #cond);\
            vx3d_exit(0);\
        }

#else
    #define VX3D_ASSERT(cond, fmt, ...)

#endif

#endif
