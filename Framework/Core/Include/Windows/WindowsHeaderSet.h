#pragma once

#ifndef _ME_WINDOWS_HEADER_SET_
#define _ME_WINDOWS_HEADER_SET_

#include "HAL/Platform.h"

#if !defined(PLATFORM_WINDOWS) || !PLATFORM_WINDOWS
  #error "Can not include this if current platform is not Windows"
#else

// include Windows specific header
  #include <Windows.h>
#endif // !defined(PLATFORM_WINDOWS) || !PLATFORM_WINDOWS

#endif // _ME_WINDOWS_HEADER_SET_
