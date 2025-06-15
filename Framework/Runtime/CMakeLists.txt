cmake_minimum_required(VERSION 3.10.0)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Src)

file(GLOB_RECURSE RUNTIME_SOURCE CONFIGURE_DEPENDS ${SRC_DIR}/*.cpp)

add_library(
  Runtime
  SHARED
  ${RUNTIME_SOURCE}
)

target_link_libraries(
  Runtime
  PRIVATE
  Core
  Application
)

target_compile_features(
  Runtime
  PRIVATE
  cxx_std_20
)

target_compile_definitions(
  Runtime
  PRIVATE
  RUNTIME_DLL_BUILD
)

target_include_directories(
  Runtime
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
    Core 
    PRIVATE 
    /W4
    /std:c++20
  )
else()
  
endif()

MEngine_setup_target(Runtime)