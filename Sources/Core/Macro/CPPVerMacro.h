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
#ifndef CPP_98
  #define CPP_98 199711L
#endif 
#ifndef HAS_CPP_98
  #define HAS_CPP_98 CPP_VER_CHECK(CPP_98)
#endif
#ifndef CPP_03
  #define CPP_03 CPP_98
#endif
#ifndef HAS_CPP_03
  #define HAS_CPP_03 CPP_VER_CHECK(CPP_03)
#endif //-CPP98/03

// CPP11
#ifndef CPP_11
  #define CPP_11 201103L
#endif
#ifndef HAS_CPP_11
  #define HAS_CPP_11 CPP_VER_CHECK(CPP_11)
#endif //-CPP11

// CPP14
#ifndef CPP_14
  #define CPP_14 201402L
#endif 
#ifndef HAS_CPP_14
  #define HAS_CPP_14 CPP_VER_CHECK(CPP_14)
#endif //-CPP14

// CPP17
#ifndef CPP_17
  #define CPP_17 201703L
#endif
#ifndef HAS_CPP_17
  #define HAS_CPP_17 CPP_VER_CHECK(CPP_17)
#endif //-CPP17

// CPP20
#ifndef CPP_20
  #define CPP_20 202002L
#endif
#ifndef HAS_CPP_20
  #define HAS_CPP_20 CPP_VER_CHECK(CPP_20)
#endif //-CPP20

//------------------------------

#endif