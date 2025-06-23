cmake_minimum_required(VERSION 3.10.0)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Src)

file(GLOB_RECURSE LAUNCH_SOURCE CONFIGURE_DEPENDS ${SRC_DIR}/*.cpp)

add_library(
  Launch
  SHARED
  ${LAUNCH_SOURCE}
)

target_link_libraries(
  Launch
  PRIVATE
  Core
  Application
)

target_compile_features(
  Launch
  PRIVATE
  cxx_std_20
)

target_compile_definitions(
  Launch
  PRIVATE
  LAUNCH_DLL_BUILD
)

target_include_directories(
  Launch
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Include  
)

if(MSVC)
  target_compile_options(
    Launch 
    PRIVATE 
    /W4
    /std:c++20
  )
else()
  
endif()

MEngine_setup_target(Launch)