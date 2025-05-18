cmake_minimum_required(VERSION 3.29.0)

file(GLOB_RECURSE CORE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp)
file(GLOB_RECURSE CORE_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h)

add_library(
  Core 
  SHARED 
  ${CORE_SOURCES} 
  ${CORE_HEADERS}
)

target_compile_features(
  Core 
  PRIVATE 
  cxx_std_20
)

# DLL define helper macro
target_compile_definitions(
  Core
  PRIVATE
  CORE_EXPORT
)

target_include_directories(
  Core 
  PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

if(MSVC)
  target_compile_options(
    Core 
    PRIVATE 
    /W4
    /std:c++20
    /FI${PROJECT_SOURCE_DIR}/CoreAPI.h
  )
else()
  
endif()
