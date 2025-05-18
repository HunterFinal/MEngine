cmake_minimum_required(VERSION 3.29.0)

file(GLOB_RECURSE OTGT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp)
file(GLOB_RECURSE OTGT_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h)

add_library(
  OTGT 
  SHARED 
  ${OTGT_SOURCES} 
  ${OTGT_HEADERS}
)

target_compile_features(
  OTGT 
  PRIVATE 
  cxx_std_20
)

# DLL define helper macro
target_compile_definitions(
  OTGT
  PRIVATE
  OTGT_EXPORT
)

target_include_directories(
  OTGT 
  PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

if(MSVC)
  target_compile_options(
    OTGT 
    PRIVATE 
    /W4
    /std:c++20
  )
else()
  
endif()