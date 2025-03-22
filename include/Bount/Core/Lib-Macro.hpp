#ifndef BOUNT_CORE_LIB_MACRO_HPP
#define BOUNT_CORE_LIB_MACRO_HPP

#include <SDKDDKVer.h>

#if defined(_DLL)
    #define BOUNT_CORE_EXPORT __declspec(dllexport)
    #define BOUNT_CORE_IMPORT __declspec(dllimport)
#elif defined(__PIC__) || defined(__pic__)
    #define BOUNT_CORE_EXPORT __attribute__((visibility("default")))
    #define BOUNT_CORE_IMPORT
#endif

#if defined(BOUNT_CORE_BUILD_API)
    #define BOUNT_CORE_API BOUNT_CORE_EXPORT
#elif defined(BOUNT_CORE_USE_API)
    #define BOUNT_CORE_API BOUNT_CORE_IMPORT
#else
    #define BOUNT_CORE_API
#endif

#ifndef BOUNT_CORE_EXPORT
    #define BOUNT_CORE_EXPORT
#endif

#ifndef BOUNT_CORE_IMPORT
    #define BOUNT_CORE_IMPORT
#endif

#ifndef BOUNT_CORE_API
    #define BOUNT_CORE_API
#endif

#endif