#ifndef VX3D_ASSERT_H
#define VX3D_ASSERT_H
#include <vrykolax3D/core/vx3d_std.h>

#ifdef VX3D_PLATFORM_PC
    #define VX3D_ASSERTION_MSG(color, level, who, file, line, msg)\
            vx3D_printf("[%s%s%s] %s%s%s:%s%s%s:%s%d%s => %s %s %s\n",\
                color, level, VX3D_ANSI_RESET, VX3D_ANSI_NOTE, who, VX3D_ANSI_RESET,\
                color, file, VX3D_ANSI_RESET, VX3D_ANSI_NOTE, line, VX3D_ANSI_RESET,\
                color, msg, VX3D_ANSI_RESET)

#else
    #error Platform is not supported.
#endif


/**
 * @brief Fatal assertions are kept in release and dist builds.
 */
#define VX3D_FATAL_ASSERT(cond)\
    if ( !(cond) )\
    {\
        VX3D_ASSERTION_MSG(VX3D_ANSI_FATAL, "ASSERTION FAILED", "Vrykolax3D", __FILE__, __LINE__, #cond);\
        vx3d_exit(0);\
    }



/**
 * @brief DEBUG only assertions.
 */
#ifdef VX3D_DEBUG_ON
    #define VX3D_ASSERT(cond)\
        if ( !(cond) )\
        {\
            VX3D_ASSERTION_MSG(VX3D_ANSI_ERROR, "ASSERTION FAILED", "Vrykolax3D", __FILE__, __LINE__, #cond);\
            vx3d_exit(0);\
        }

#else
    #define VX3D_ASSERT(cond)

#endif

#endif
