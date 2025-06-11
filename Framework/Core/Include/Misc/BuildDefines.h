#pragma once

#ifndef _ME_BUILD_DEFINES_
#define _ME_BUILD_DEFINES_

/**
 * Build configuration from CMake
 */

#ifndef ME_DEBUG_ON
  #define ME_DEBUG_ON 0
#endif
#ifndef ME_RELEASE_ON
  #define ME_RELEASE_ON 0
#endif

// TODO Unuse now
#ifndef ME_DEVELOPMENT_ON
  #define ME_DEVELOPMENT_ON 0
#endif

#if !(ME_DEBUG_ON || ME_RELEASE_ON || ME_DEVELOPMENT_ON)
  #error Should set either of ME_DEBUG_ON, ME_RELEASE_ON, ME_DEVELOPMENT_ON as 1
#endif

/**
 * Debug options depend on build configuration
 */

 /**
  * ME_ASSERT_ON      If true, then turn on assertion
  */

#if ME_DEBUG_ON
  #ifndef ME_ASSERT_ON
    #define ME_ASSERT_ON  1
  #endif
  #ifndef ME_DEBUG_LOGGING
    #define ME_DEBUG_LOGGING 1
  #endif
#endif

#if ME_RELEASE_ON
  #ifndef ME_ASSERT_ON
    #define ME_ASSERT_ON  0
  #endif 
  #ifndef ME_DEBUG_LOGGING
    #define ME_DEBUG_LOGGING 0
  #endif
#endif

#endif // _ME_BUILD_DEFINES_