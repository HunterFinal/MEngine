#ifdef _WIN32
#pragma once
#endif

#ifndef MENGINE_CPP_VERSION
#define MENGINE_CPP_VERSION

#if defined(__clang__) || defined(__GNUC__)
  #define CPP_STANDARD __cpluspluc
#elif defined(_MSC_VER)
  #define CPP_STANDARD _MSVC_LANG
#endif

//-------------------------------
//* CPP Version Def
//-------------------------------
#define CPP_VER_CHECK(Version) (!!(CPP_STANDARD >= Version))

// CPP98/03
#ifndef HAS_CPP_98
  #define HAS_CPP_98 CPP_VER_CHECK(199711L)
#endif
#ifndef HAS_CPP_03
  #define HAS_CPP_03 HAS_CPP_98
#endif

// CPP11
#ifndef HAS_CPP_11
  #define HAS_CPP_11 CPP_VER_CHECK(201103L)
#endif

// CPP14
#ifndef HAS_CPP_14
  #define HAS_CPP_14 CPP_VER_CHECK(201402L)
#endif

// CPP17
#ifndef HAS_CPP_17
  #define HAS_CPP_17 CPP_VER_CHECK(201703L)
#endif

// CPP20
#ifndef HAS_CPP_20
  #define HAS_CPP_20 CPP_VER_CHECK(202002L)
#endif

//------------------------------

#endif // MENGINE_CPP_VERSION