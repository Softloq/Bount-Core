/**
 * @file StandardMacros.hpp
 * @brief Standard Core Macros. This is included in all core headers.
 * @author Brandon Foster (Paradox Gene)
 */

#ifndef BOUNT_CORE_STANDARD_MACROS_HPP
#define BOUNT_CORE_STANDARD_MACROS_HPP

/**
 * Main Macros:
 * BOUNT_CORE_API - Must be prefixed in all classes and functions.
 * 
 * BOUNT_DEBUG - Defined when debug information should be provided.
 * 
 * BOUNT_MSVC  - Defined when the libraries are compiled with Microsoft C++ compiler.
 * BOUNT_CLANG - Defined when the libraries are compiled with Clang C++ compiler.
 * BOUNT_GCC   - Defined when the libraries are compiled with GNU C++ compiler.
 * 
 * BOUNT_WINDOWS - Defined when the libraries are compiled for Windows.
 * BOUNT_LINUX   - Defined when the libraries are compiled for Linux.
 * BOUNT_MACOS   - Defined when the libraries are compiled for macOS.
 */

#if defined(_DEBUG) || !defined(NDEBUG) || defined(DEBUG)
    #define BOUNT_DEBUG
#endif

#if defined(_MSC_VER)
    #define BOUNT_MSVC
    #define BOUNT_CORE_EXPORT __declspec(dllexport)
    #define BOUNT_CORE_IMPORT __declspec(dllimport)
#elif defined(__clang__)
    #define BOUNT_CLANG
    #define BOUNT_CORE_EXPORT __attribute__((visibility("default")))
    #define BOUNT_CORE_IMPORT
#elif defined(__GNUC__)
    #define BOUNT_GCC
    #define BOUNT_CORE_EXPORT __attribute__((visibility("default")))
    #define BOUNT_CORE_IMPORT
#endif

#if defined(_WIN32)
    #define BOUNT_WINDOWS
#elif defined(__linux__)
    #define BOUNT_LINUX
#elif defined(__APPLE__)
    #define BOUNT_MACOS
#else
    #error "Operating System is not supported."
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