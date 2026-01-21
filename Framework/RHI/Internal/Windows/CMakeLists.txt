cmake_minimum_required(VERSION 3.29.0)

file(GLOB_RECURSE RHI_PLATFORM_SOURCES CMAKE_CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(
  Platform_RHI_Impl
  INTERFACE
)

target_sources(
  Platform_RHI_Impl
  INTERFACE
  ${RHI_PLATFORM_SOURCES}
)

target_include_directories(
  Platform_RHI_Impl
  INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/..
)

message(STATUS "RHI : Windows platform")

