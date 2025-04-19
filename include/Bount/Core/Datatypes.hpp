/**
 * @file Datatypes.hpp
 * @brief Standard Datatypes.
 * @author Brandon Foster (Paradox Gene)
 */

#ifndef BOUNT_CORE_DATATYPES_HPP
#define BOUNT_CORE_DATATYPES_HPP

#include "Bount/Core/StandardMacros.hpp"
#include <cstdint>
#include <cctype>
#include <string>

namespace Bount
{
typedef bool B8;
static_assert(sizeof(B8) == 1, "Datatype B8 must be 1 byte.");

typedef uint8_t  U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;
static_assert(sizeof(U8)  == 1, "Datatype U8 must be 1 byte.");
static_assert(sizeof(U16) == 2, "Datatype U16 must be 2 bytes.");
static_assert(sizeof(U32) == 4, "Datatype U32 must be 4 bytes.");
static_assert(sizeof(U64) == 8, "Datatype U64 must be 8 bytes.");

typedef int8_t  I8;
typedef int16_t I16;
typedef int32_t I32;
typedef int64_t I64;
static_assert(sizeof(I8)  == 1, "Datatype I8 must be 1 byte.");
static_assert(sizeof(I16) == 2, "Datatype I16 must be 2 bytes.");
static_assert(sizeof(I32) == 4, "Datatype I32 must be 4 bytes.");
static_assert(sizeof(I64) == 8, "Datatype I64 must be 8 bytes.");

typedef float  F32;
typedef double F64;
static_assert(sizeof(F32) == 4, "Datatype F32 must be 4 bytes.");
static_assert(sizeof(F64) == 8, "Datatype F64 must be 8 bytes.");

typedef long double FMax;
static_assert(sizeof(FMax) >= sizeof(F64), "Datatype FMax must be greater than or equal to F64.");

typedef char C8;
typedef char Char;
static_assert(sizeof(C8)   == 1, "Datatype C8 must be 1 byte.");
static_assert(sizeof(Char) == 1, "Datatype Char must be 1 byte.");

typedef char8_t UC8;
typedef char8_t Char8;
static_assert(sizeof(UC8)   == 1, "Datatype UC8 must be 1 byte.");
static_assert(sizeof(Char8) == 1, "Datatype Char8 must be 1 byte.");

typedef char16_t UC16;
typedef char16_t Char16;
static_assert(sizeof(UC16)   == 2, "Datatype UC16 must be 2 bytes.");
static_assert(sizeof(Char16) == 2, "Datatype Char16 must be 2 bytes.");

typedef char32_t UC32;
typedef char32_t Char32;
static_assert(sizeof(UC32)   == 4, "Datatype UC32 must be 4 bytes.");
static_assert(sizeof(Char32) == 4, "Datatype Char32 must be 4 bytes.");

typedef char Byte;
static_assert(sizeof(Byte) == 1, "Datatype Byte must be 1 byte.");

typedef size_t SizeT;
typedef std::string String;
}

#endif