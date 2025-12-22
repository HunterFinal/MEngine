cmake_minimum_required(VERSION 3.29.0)

file(GLOB_RECURSE RHI_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp)


add_library(
  RHI 
  SHARED 
  ${RHI_SOURCES} 
)
  
if (WIN32)
  add_subdirectory(Internal/Windows)
endif()

target_link_libraries(
  RHI
  PUBLIC
  Core
)

target_include_directories(
  RHI
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Include
  ${CMAKE_CURRENT_SOURCE_DIR}/Internal
)

target_compile_features(
  RHI 
  PRIVATE 
  cxx_std_20
)

# DLL define helper macro
target_compile_definitions(
  RHI
  PRIVATE
  RHI_EXPORT
)

target_include_directories(
  RHI 
  PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

target_include_directories(
  RHI
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/Internal
)

if(MSVC)
  target_compile_options(
    RHI 
    PRIVATE 
    /W4
    /std:c++20
  )
else()
  
endif()

MEngine_setup_target(RHI)

