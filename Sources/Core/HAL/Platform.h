#ifdef _WIN32
#pragma once
#endif

#ifndef MENGINE_HAL_PLATFORM
#define MENGINE_HAL_PLATFORM

#include "HAL/PreprocessorHelpers.h"

#include PLATFORM_HEADER(Platform.h)

//~Global types base

// 8-bit unsigned integer
TYPEDEF(MPlatformTypes::uint8, uint8);
// 16-bit unsigned integer
TYPEDEF(MPlatformTypes::uint16, uint16);
// 32-bit unsigned integer
TYPEDEF(MPlatformTypes::uint32, uint32);
// 64-bit unsigned integer
TYPEDEF(MPlatformTypes::uint64, uint64);
// 8-bit signed integer
TYPEDEF(MPlatformTypes::int8, int8);
// 16-bit signed integer
TYPEDEF(MPlatformTypes::int16, int16);
// 32-bit signed integer
TYPEDEF(MPlatformTypes::int32, int32);
// 64-bit signed integer
TYPEDEF(MPlatformTypes::int64, int64);
// 7-bit character(8-bit fixed)
TYPEDEF(MPlatformTypes::ANSICHAR, ANSICHAR);
// ?-bit character(depends on platform)
TYPEDEF(MPlatformTypes::WIDECHAR, WIDECHAR);
// Unicode 8-bit character
TYPEDEF(MPlatformTypes::UTF8CHAR, UTF8CHAR);
// Unicode 16-bit character
TYPEDEF(MPlatformTypes::UTF16CHAR, UTF16CHAR);
// Unicode 32-bit character
TYPEDEF(MPlatformTypes::UTF32CHAR, UTF32CHAR);

TYPEDEF(MPlatformTypes::SIZE_T, SIZE_T);

TYPEDEF(MPlatformTypes::SSIZE_T, SSIZE_T);
// NULL type
TYPEDEF(MPlatformTypes::TYPE_NULL, TYPE_NULL);
// nullptr type
TYPEDEF(MPlatformTypes::TYPE_NULLPTR, TYPE_NULLPTR);

#endif