// MEngine platform header definitions
#pragma once

#ifndef _ME_PLATFORM_HEADER_
#define _ME_PLATFORM_HEADER_

#if defined(_WIN32) || defined(_WIN64)
  #define PLATFORM_HEADER_NAME Windows
  #define PLATFORM_WINDOWS 1
  #define PLATFORM_MICROSOFT 1
#elif defined(__unix) || defined(__unix__) 
  #define PLATFORM_HEADER_NAME Unix
  #define PLATFORM_UNIX 1
#elif defined(__linux__)
  #define PLATFORM_HEADER_NAME Linux
  #define PLATFORM_LINUX 1
#else
  #error "Undefined platform"
#endif 
 
#endif // _ME_PLATFORM_HEADER_
