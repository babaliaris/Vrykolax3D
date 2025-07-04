#include <vrykolax3D/core/vx3d_std.h>

void vx3D_printf(const char *fmt, ...)
{
    #ifdef VX3D_PLATFORM_PC
        va_list args;
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
    #else
        #error Platform not supported.
    #endif
}

void *vx3D_malloc(VX3D_SIZE_T size)
{
    #ifdef VX3D_PLATFORM_PC
        return malloc(size);
    #else
        #error Platform not supported.
    #endif
}

void vx3D_free(void *ptr)
{
    #ifdef VX3D_PLATFORM_PC
        free(ptr);
    #else
        #error Platform not supported.
    #endif
}

void *vx3D_memset(void *dst, int value, VX3D_SIZE_T size)
{
    #ifdef VX3D_PLATFORM_PC
        return memset(dst, value, size);
    #else
        #error Platform not supported.
    #endif
}

void *vx3D_memcpy(void *dst, const void *src, VX3D_SIZE_T size)
{
    #ifdef VX3D_PLATFORM_PC
        return memcpy(dst, src, size);
    #else
        #error Platform not supported.
    #endif
}

void *vx3D_memmove(void *dst, const void *src, VX3D_SIZE_T size)
{
    #ifdef VX3D_PLATFORM_PC
        return memmove(dst, src, size);
    #else
        #error Platform not supported.
    #endif
}

int vx3D_memcmp(const void *a, const void *b, VX3D_SIZE_T size)
{
    #ifdef VX3D_PLATFORM_PC
        return memcmp(a, b, size);
    #else
        #error Platform not supported.
    #endif
}

char *vx3D_strcpy(char *dst, const char *src)
{
    #ifdef VX3D_PLATFORM_PC
        return strcpy(dst, src);
    #else
        #error Platform not supported.
    #endif
}

char *vx3D_strncpy(char *dst, const char *src, VX3D_SIZE_T n)
{
    #ifdef VX3D_PLATFORM_PC
        return strncpy(dst, src, n);
    #else
        #error Platform not supported.
    #endif
}

char *vx3D_strcat(char *dst, const char *src)
{
    #ifdef VX3D_PLATFORM_PC
        return strcat(dst, src);
    #else
        #error Platform not supported.
    #endif
}

int vx3D_strcmp(const char *a, const char *b)
{
    #ifdef VX3D_PLATFORM_PC
        return strcmp(a, b);
    #else
        #error Platform not supported.
    #endif
}

int vx3D_strncmp(const char *a, const char *b, VX3D_SIZE_T n)
{
    #ifdef VX3D_PLATFORM_PC
        return strncmp(a, b, n);
    #else
        #error Platform not supported.
    #endif
}

VX3D_SIZE_T vx3D_strlen(const char *str)
{
    #ifdef VX3D_PLATFORM_PC
        return strlen(str);
    #else
        #error Platform not supported.
    #endif
}

char *vx3D_strchr(const char *str, int c)
{
    #ifdef VX3D_PLATFORM_PC
        return strchr(str, c);
    #else
        #error Platform not supported.
    #endif
}

char *vx3D_strstr(const char *haystack, const char *needle)
{
    #ifdef VX3D_PLATFORM_PC
        return strstr(haystack, needle);
    #else
        #error Platform not supported.
    #endif
}

int vx3D_sprintf(char *dst, const char *fmt, ...)
{
    #ifdef VX3D_PLATFORM_PC
        va_list args;
        va_start(args, fmt);
        int result = vsprintf(dst, fmt, args); // Unsafe if dst buffer is too small
        va_end(args);
        return result;
    #else
        #error Platform not supported.
    #endif
}

int vx3D_snprintf(char *dst, VX3D_SIZE_T size, const char *fmt, ...)
{
    #ifdef VX3D_PLATFORM_PC
        va_list args;
        va_start(args, fmt);
        int result = vsnprintf(dst, size, fmt, args); // Safe — limits write to `size`
        va_end(args);
        return result;
    #else
        #error Platform not supported.
    #endif
}
