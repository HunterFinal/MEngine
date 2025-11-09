cmake_minimum_required(VERSION 3.29.0)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Src)

file(GLOB_RECURSE ECS_CORE_SOURCES CONFIGURE_DEPENDS ${SRC_DIR}/*.cpp)

add_library(
  ECSCore
  SHARED
  ${ECS_CORE_SOURCES}
)

target_link_libraries(
  ECSCore
  PRIVATE
  Core
)

target_compile_features(
  ECSCore
  PRIVATE
  cxx_std_20
)

target_compile_definitions(
  ECSCore
  PRIVATE
  ECS_CORE_DLL_BUILD
)

target_include_directories(
  ECSCore
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Include  
  PRIVATE
  ${CMAKE_SOURCE_DIR}/Framework/Core 
  ${CMAKE_SOURCE_DIR}/Framework/Core/Include
)

if(MSVC)
  target_compile_options(
    ECSCore 
    PRIVATE 
    /W4
    /std:c++20
  )
else()
  
endif()

MEngine_setup_target(ECSCore)