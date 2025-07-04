#ifndef VX3D_LOGGER_H
#define VX3D_LOGGER_H
#include <vrykolax3D/core/vx3d_std.h>

#ifdef VX3D_DEBUG_ON

    #ifdef VX3D_PLATFORM_PC
        #define VX3D_COLORFUL_LOG(color, level, who, file, line, fmt, ...)\
            vx3D_printf("[%s%s%s] %s%s%s:%s%s%s:%s%d%s => %s" fmt "%s\n",\
                color, level, VX3D_ANSI_RESET, VX3D_ANSI_NOTE, who, VX3D_ANSI_RESET,\
                color, file, VX3D_ANSI_RESET, VX3D_ANSI_NOTE, line, VX3D_ANSI_RESET,\
                color, ##__VA_ARGS__, VX3D_ANSI_RESET)

        #define VX3D_COLORFUL_LOG_MSG(color, level, who, file, line, msg)\
            vx3D_printf("[%s%s%s] %s%s%s:%s%s%s:%s%d%s => %s %s %s\n",\
                color, level, VX3D_ANSI_RESET, VX3D_ANSI_NOTE, who, VX3D_ANSI_RESET,\
                color, file, VX3D_ANSI_RESET, VX3D_ANSI_NOTE, line, VX3D_ANSI_RESET,\
                color, msg, VX3D_ANSI_RESET)

        #define VX3D_TRACE(fmt, ...)\
            VX3D_COLORFUL_LOG(VX3D_ANSI_TRACE, "TRACE", "Vrykolax3D", __FILE__, __LINE__, fmt, ##__VA_ARGS__);

        #define VX3D_INFO(fmt, ...)\
            VX3D_COLORFUL_LOG(VX3D_ANSI_INFO, "INFO", "Vrykolax3D", __FILE__, __LINE__, fmt, ##__VA_ARGS__);

        #define VX3D_WARN(fmt, ...)\
            VX3D_COLORFUL_LOG(VX3D_ANSI_WARN, "WARN", "Vrykolax3D", __FILE__, __LINE__, fmt, ##__VA_ARGS__);

        #define VX3D_ERROR(fmt, ...)\
            VX3D_COLORFUL_LOG(VX3D_ANSI_ERROR, "ERROR", "Vrykolax3D", __FILE__, __LINE__, fmt, ##__VA_ARGS__);

        #define VX3D_FATAL(fmt, ...)\
            VX3D_COLORFUL_LOG(VX3D_ANSI_FATAL, "FATAL", "Vrykolax3D", __FILE__, __LINE__, fmt, ##__VA_ARGS__);
    #else
        #error Platform is not supported.
    #endif

#else
    #define VX3D_COLORFUL_LOG(color, level, who, file, line, fmt, ...)

    #define VX3D_COLORFUL_LOG_MSG(color, level, who, file, line, msg)

    #define VX3D_TRACE(fmt, ...)

    #define VX3D_INFO(fmt, ...)

    #define VX3D_WARN(fmt, ...)

    #define VX3D_ERROR(fmt, ...)

    #define VX3D_FATAL(fmt, ...)

#endif

#endif
