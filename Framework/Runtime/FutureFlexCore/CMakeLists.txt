cmake_minimum_required(VERSION 3.10.0)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Src)

file(GLOB_RECURSE FUTURE_FLEX_CORE_SOURCE CONFIGURE_DEPENDS ${SRC_DIR}/*.cpp)

add_library(
  FutureFlexCore
  SHARED
  ${FUTURE_FLEX_CORE_SOURCE}
)

target_link_libraries(
  FutureFlexCore
  PRIVATE
  Core
  Application
)

target_compile_features(
  FutureFlexCore
  PRIVATE
  cxx_std_20
)

target_compile_definitions(
  FutureFlexCore
  PRIVATE
  FUTUREFLEX_CORE_DLL_BUILD
)

target_include_directories(
  FutureFlexCore
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Include  
  PRIVATE
  ${CMAKE_SOURCE_DIR}/Framework/Core 
  ${CMAKE_SOURCE_DIR}/Framework/Core/Include
  ${CMAKE_SOURCE_DIR}/Framework/Application
  ${CMAKE_SOURCE_DIR}/Framework/Application/Include
)

if(MSVC)
  target_compile_options(
    FutureFlexCore 
    PRIVATE 
    /W4
    /std:c++20
  )
else()
  
endif()

MEngine_setup_target(FutureFlexCore)