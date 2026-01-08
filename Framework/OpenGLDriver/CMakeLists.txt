cmake_minimum_required(VERSION 3.29.0)

file(GLOB_RECURSE OPENGLDRV_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp)
file(GLOB_RECURSE OPENGLDRV_PRIVATE_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.h)

add_library(
  OpenGLDriver 
  SHARED 
  ${OPENGLDRV_SOURCES}
  ${OPENGLDRV_PRIVATE_HEADERS}
)

if (WIN32)
  add_subdirectory(Internal/Windows)

  target_link_libraries(
    OpenGLDriver
    PRIVATE
    opengl32
  )
endif()

target_link_libraries(
  OpenGLDriver
  PUBLIC
  Core
  RHI
  Platform_OpenGLDrv_Impl
)

# glad
add_library(
  glad
  STATIC
  ${CMAKE_SOURCE_DIR}/Framework/ThirdParty/OpenGL/glad/glad.c
)

target_include_directories(
  glad
  PUBLIC
  ${CMAKE_SOURCE_DIR}/Framework/ThirdParty/OpenGL
)

target_compile_features(
  OpenGLDriver 
  PRIVATE 
  cxx_std_20
)

# DLL define helper macro
target_compile_definitions(
  OpenGLDriver
  PRIVATE
  OPENGLDRV_EXPORT
)

target_include_directories(
  OpenGLDriver 
  PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Include
  ${CMAKE_SOURCE_DIR}/Framework/ThirdParty/OpenGL
)

target_include_directories(
  OpenGLDriver
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/Src
  ${CMAKE_CURRENT_SOURCE_DIR}/Internal
)

target_link_libraries(
  OpenGLDriver
  PRIVATE
  glad
)

if(MSVC)
  target_compile_options(
    OpenGLDriver 
    PRIVATE 
    /W4
    /std:c++20
  )
else()
  
endif()

MEngine_setup_target(OpenGLDriver)