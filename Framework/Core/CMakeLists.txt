cmake_minimum_required(VERSION 3.29.0)

file(GLOB_RECURSE CORE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp)

add_library(
  Core 
  SHARED 
  ${CORE_SOURCES} 
)

target_link_libraries(
  Core
  PUBLIC
  spdlog::spdlog
)

target_include_directories(
  Core
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
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
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

target_include_directories(
  Core
  PRIVATE
  &{CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty
)

if(MSVC)
  target_compile_options(
    Core 
    PRIVATE 
    /W4
    /std:c++20
    /FI${PROJECT_SOURCE_DIR}/Framework/CoreAPI.h
  )
else()
  
endif()
