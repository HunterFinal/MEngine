cmake_minimum_required(VERSION 3.29.0)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Src)

file(GLOB_RECURSE INPUT_CORE_SOURCE CONFIGURE_DEPENDS ${SRC_DIR}/*.cpp)

add_library(
  InputCore
  SHARED
  ${INPUT_CORE_SOURCE}
)

target_link_libraries(
  InputCore
  PRIVATE
  Core
)

target_compile_features(
  InputCore
  PRIVATE
  cxx_std_20
)

target_compile_definitions(
  InputCore
  PRIVATE
  INPUT_CORE_DLL_BUILD
)

target_include_directories(
  InputCore
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Include  
  PRIVATE
  ${CMAKE_SOURCE_DIR}/Framework/Core 
  ${CMAKE_SOURCE_DIR}/Framework/Core/Include
  ${CMAKE_CURRENT_SOURCE_DIR}/Internal
)

if(MSVC)
  target_compile_options(
    InputCore 
    PRIVATE 
    /W4
    /std:c++20
  )
else()
  
endif()

MEngine_setup_target(InputCore)