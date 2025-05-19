cmake_minimum_required(VERSION 3.29.0)

file(GLOB_RECURSE APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp)

add_library(
  APP 
  SHARED 
  ${APP_SOURCES} 
)

target_compile_features(
  APP 
  PRIVATE 
  cxx_std_20
)

# DLL define helper macro
target_compile_definitions(
  APP
  PRIVATE
  APP_DLL_BUILD
)

target_include_directories(
  APP 
  PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

if(MSVC)
  target_compile_options(
    APP 
    PRIVATE 
    /W4
    /std:c++20
  )
else()
  
endif()