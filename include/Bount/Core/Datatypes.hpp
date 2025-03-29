#ifndef BOUNT_CORE_DATATYPES_HPP
#define BOUNT_CORE_DATATYPES_HPP

#include "Bount/Core/Lib-Macro.hpp"
#include <cstdint>
#include <cctype>
#include <string>

namespace Bount
{
typedef bool B8;

typedef uint8_t  U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

typedef int8_t  I8;
typedef int16_t I16;
typedef int32_t I32;
typedef int64_t I64;

typedef float       F32;
typedef double      F64;
typedef long double FMaxT;

typedef char     C8;
typedef char     Char;

typedef char8_t  UC8;
typedef char8_t  Char8;

typedef char16_t UC16;
typedef char16_t Char16;

typedef char32_t UC32;
typedef char32_t Char32;

typedef size_t SizeT;
typedef char   Byte;

typedef std::string String;
}

#endif