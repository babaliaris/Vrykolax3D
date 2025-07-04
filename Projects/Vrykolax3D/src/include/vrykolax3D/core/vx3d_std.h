#ifndef VX3D_STD_H
#define VX3D_STD_H
#include <vrykolax3D/core/vx3d_api.h>

/**
 * @file
 * @brief The standard library of Vrykolax3D.
 * 
 * This file contains abstractions of common C
 * standard functionality. Although most compilers
 * support them, we still abstract them by wrapping
 * then in our custom vx3D_ namespace just in case.
 */


#if VX3D_PLATFORM_PC

    //Some standard libs.
    #include <stdio.h>  // Standard C stuff.
    #include <stdlib.h> // For dynamic memory.
    #include <stdarg.h> // For va args.
    #include <stdint.h> // For fixed type integers.
    #include <stddef.h> // For size_t, offsetof
    #include <string.h> // C string operations, memcpy, memset, etc.

    //Ansi Colors (Windows 10, version 1511 (November Update, released November 2015) and later).
    #define VX3D_ANSI_RESET "\033[0m"
    #define VX3D_ANSI_TRACE "\033[37m"
    #define VX3D_ANSI_INFO  "\033[32m"
    #define VX3D_ANSI_WARN  "\033[33m"
    #define VX3D_ANSI_ERROR "\033[31m"
    #define VX3D_ANSI_FATAL "\033[41m"
    #define VX3D_ANSI_DEBUG "\033[36m"
    #define VX3D_ANSI_NOTE  "\033[35m"

    //Fixed size types.
    #define VX3D_SIZE_T   size_t
    #define VX3D_INT8     int8_t
    #define VX3D_INT16    int16_t
    #define VX3D_INT32    int32_t
    #define VX3D_INT64    int64_t
    #define VX3D_UINT8    uint8_t
    #define VX3D_UINT16   uint16_t
    #define VX3D_UINT32   uint32_t
    #define VX3D_UINT64   uint64_t

    //Usefull macros.
    #define VX3D_SIZEOF(type) sizeof(type)
    #define VX3D_OFFSETOF(type, member) offsetof(type, member)

#else
    #error Platform not supported...
#endif


#define VX3D_COND(cond, x)\
    if ( (cond) ) {x;}



/** 
 * @brief Stops the programm and exits with a status code.
 * 
 * This function wraps the standard `exit` function.
 * 
 * @param[in] int The status reason of the exit.
 */
VX3D_EXTERN_C VX3D_API void vx3d_exit(int status);



/** 
 * @brief Prints formatted output to the standard output.
 * 
 * This function wraps the standard `vprintf` function to print formatted strings
 * using variable argument lists. Output is directed to `stdout`.
 * 
 * @param[in] fmt The format string.
 * @param[in] ... Variable arguments matching the format string.
 */
VX3D_EXTERN_C VX3D_API void vx3D_printf(const char *fmt, ...);

/**
 * @brief Allocates memory on the heap.
 *
 * This function wraps `malloc` to allocate a block of memory of the given size.
 *
 * @param[in] size The number of bytes to allocate.
 * @return A pointer to the allocated memory, or NULL if allocation fails.
 */
VX3D_EXTERN_C VX3D_API void *vx3D_malloc(VX3D_SIZE_T size);

/**
 * @brief Frees memory previously allocated.
 *
 * This function wraps `free` to deallocate memory that was allocated using `vx3D_malloc`.
 *
 * @param[in] ptr Pointer to the memory block to free.
 */
VX3D_EXTERN_C VX3D_API void vx3D_free(void *ptr);

/**
 * @brief Fills a block of memory with a specific value.
 *
 * This function wraps `memset`, setting each byte in the block to the specified value.
 *
 * @param[out] dst Pointer to the destination memory block.
 * @param[in] value Value to set.
 * @param[in] size Number of bytes to set.
 * @return A pointer to the destination memory block.
 */
VX3D_EXTERN_C VX3D_API void *vx3D_memset(void *dst, int value, VX3D_SIZE_T size);

/**
 * @brief Copies a block of memory.
 *
 * This function wraps `memcpy`. It copies `size` bytes from `src` to `dst`.
 * Behavior is undefined if the memory regions overlap.
 *
 * @param[out] dst Pointer to the destination memory block.
 * @param[in] src Pointer to the source memory block.
 * @param[in] size Number of bytes to copy.
 * @return A pointer to the destination memory block.
 */
VX3D_EXTERN_C VX3D_API void *vx3D_memcpy(void *dst, const void *src, VX3D_SIZE_T size);

/**
 * @brief Moves a block of memory safely, allowing overlap.
 *
 * This function wraps `memmove`. It correctly handles overlapping memory regions.
 *
 * @param[out] dst Pointer to the destination memory block.
 * @param[in] src Pointer to the source memory block.
 * @param[in] size Number of bytes to move.
 * @return A pointer to the destination memory block.
 */
VX3D_EXTERN_C VX3D_API void *vx3D_memmove(void *dst, const void *src, VX3D_SIZE_T size);

/**
 * @brief Compares two blocks of memory.
 *
 * This function wraps `memcmp` and compares `size` bytes of memory.
 *
 * @param[in] a Pointer to the first memory block.
 * @param[in] b Pointer to the second memory block.
 * @param[in] size Number of bytes to compare.
 * @return An integer less than, equal to, or greater than zero if `a` is found 
 *         to be less than, equal to, or greater than `b`.
 */
VX3D_EXTERN_C VX3D_API int vx3D_memcmp(const void *a, const void *b, VX3D_SIZE_T size);

/**
 * @brief Copies a null-terminated string.
 *
 * This function wraps `strcpy`. It does not perform bounds checking and is unsafe
 * if the destination buffer is too small.
 *
 * @warning This function is unsafe and may cause buffer overflows.
 *
 * @param[out] dst Destination buffer.
 * @param[in] src Source null-terminated string.
 * @return A pointer to the destination string.
 */
VX3D_EXTERN_C VX3D_API char *vx3D_strcpy(char *dst, const char *src);

/**
 * @brief Copies up to n characters of a string.
 *
 * This function wraps `strncpy`. If the source string is shorter than `n`, the destination
 * will be null-padded. If not null-terminated, you must handle termination manually.
 *
 * @param[out] dst Destination buffer.
 * @param[in] src Source string.
 * @param[in] n Maximum number of characters to copy.
 * @return A pointer to the destination buffer.
 */
VX3D_EXTERN_C VX3D_API char *vx3D_strncpy(char *dst, const char *src, VX3D_SIZE_T n);

/**
 * @brief Appends one string to another.
 *
 * This function wraps `strcat`. It appends the null-terminated string `src` to the end of `dst`.
 *
 * @warning This function is unsafe and may cause buffer overflows if `dst` does not have
 *          enough space.
 *
 * @param[out] dst Destination string (must be null-terminated and large enough).
 * @param[in] src Source string to append.
 * @return A pointer to the destination string.
 */
VX3D_EXTERN_C VX3D_API char *vx3D_strcat(char *dst, const char *src);

/**
 * @brief Compares two null-terminated strings.
 *
 * This function wraps `strcmp`. It performs a lexicographical comparison.
 *
 * @param[in] a First string.
 * @param[in] b Second string.
 * @return An integer less than, equal to, or greater than zero.
 */
VX3D_EXTERN_C VX3D_API int vx3D_strcmp(const char *a, const char *b);

/**
 * @brief Compares up to n characters of two strings.
 *
 * This function wraps `strncmp`, comparing at most `n` characters.
 *
 * @param[in] a First string.
 * @param[in] b Second string.
 * @param[in] n Maximum number of characters to compare.
 * @return An integer less than, equal to, or greater than zero.
 */
VX3D_EXTERN_C VX3D_API int vx3D_strncmp(const char *a, const char *b, VX3D_SIZE_T n);

/**
 * @brief Returns the length of a null-terminated string.
 *
 * This function wraps `strlen`.
 *
 * @param[in] str The input string.
 * @return The number of characters before the null terminator.
 */
VX3D_EXTERN_C VX3D_API VX3D_SIZE_T vx3D_strlen(const char *str);

/**
 * @brief Finds the first occurrence of a character in a string.
 *
 * This function wraps `strchr`.
 *
 * @param[in] str The string to search.
 * @param[in] c The character to locate.
 * @return A pointer to the first occurrence of `c`, or NULL if not found.
 */
VX3D_EXTERN_C VX3D_API char *vx3D_strchr(const char *str, int c);

/**
 * @brief Finds the first occurrence of a substring in a string.
 *
 * This function wraps `strstr`.
 *
 * @param[in] haystack The string to search in.
 * @param[in] needle The substring to search for.
 * @return A pointer to the first occurrence of `needle`, or NULL if not found.
 */
VX3D_EXTERN_C VX3D_API char *vx3D_strstr(const char *haystack, const char *needle);

/**
 * @brief Writes formatted data to a string.
 *
 * This function wraps `vsprintf` and is considered unsafe because it does not
 * perform bounds checking.
 *
 * @warning This function is unsafe and may cause buffer overflows.
 *
 * @param[out] dst Destination buffer for the formatted string.
 * @param[in] fmt Format string.
 * @param[in] ... Variable arguments matching the format string.
 * @return The number of characters written (excluding null terminator).
 */
VX3D_EXTERN_C VX3D_API int vx3D_sprintf(char *dst, const char *fmt, ...);

/**
 * @brief Writes formatted data to a string with buffer size checking.
 *
 * This function wraps `vsnprintf` and is considered safe because it respects the buffer size.
 *
 * @param[out] dst Destination buffer for the formatted string.
 * @param[in] size Maximum number of bytes to write (including null terminator).
 * @param[in] fmt Format string.
 * @param[in] ... Variable arguments matching the format string.
 * @return The number of characters that would have been written if enough space were available.
 */
VX3D_EXTERN_C VX3D_API int vx3D_snprintf(char *dst, VX3D_SIZE_T size, const char *fmt, ...);


#endif