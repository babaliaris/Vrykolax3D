#ifndef VX3D_CORE_H
#define VX3D_CORE_H

// Detect C++ to wrap with extern "C"
#ifdef __cplusplus
    #define VX3D_EXTERN_C extern "C"
#else
    #define VX3D_EXTERN_C
#endif

// Platform-specific symbol export
#if defined(_MSC_VER) && defined(VX3D_OS_WINDOWS)

    //STATIC LIBS
    #if defined(VX3D_STATIC_LIB)
        #define VX3D_API

    //SHARED LIBS
    #else
        #if defined(VX3D_SHARED_LIB)
            #define VX3D_API __declspec(dllexport)
        #else
            #define VX3D_API __declspec(dllimport)
        #endif
    #endif

// Linux, macOS
#elif defined(VX3D_OS_LINUX) || defined(VX3D_OS_MACOSX)

    #if defined(VX3D_STATIC_LIB)
        #define VX3D_API
    #else
        #define VX3D_API __attribute__((visibility("default")))
    #endif

//Uknown Platform.
#else
    #error Platform is not supported...
#endif


#if defined(_MSC_VER)
  #define VX3D_ALIGN16 __declspec(align(16))
  #define VX3D_ALIGN_UP(p, align) (((p) + ((align)-1)) & ~((align)-1))

#elif defined(__GNUC__) || defined(__clang__) || defined(__INTEL_COMPILER)
  #define VX3D_ALIGN16 __attribute__((aligned(16)))
  #define VX3D_ALIGN_UP(p, align) (((p) + ((align)-1)) & ~((align)-1))

#else
  #error "Unknown compiler, please define ALIGN16 for your compiler"
#endif


#endif