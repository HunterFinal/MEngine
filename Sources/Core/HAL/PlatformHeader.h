#ifdef _WIN32
#pragma once
#endif

#ifndef MENGINE_PLATFORM_HEADER
#define MENGINE_PLATFORM_HEADER

#if defined(_WIN32)
  #define PLATFORM_HEADER_NAME Windows
#elif defined(__unix) || defined(__unix__)
  #define PLATFORM_HEADER_NAME Unix
#else
  #define PLATFORM_HEADER_NAME
  #error "Undefined platform"
#endif // defined(_WIN32)
 
#endif // MENGINE_PLATFORM_HEADER
