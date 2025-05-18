cmake_minimum_required(VERSION 3.29.0)

# use this BEFORE project()
# can not generate compile_commands.json when using MSVC,
# use Ninja to generate
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(MEngine VERSION 0.1.0 LANGUAGES C CXX)

add_executable(MEngine ${CMAKE_CURRENT_SOURCE_DIR}/EntryPoint.cpp)
target_compile_features(MEngine PRIVATE cxx_std_20)
set_target_properties(
  MEngine
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/../Execution/Debug"
  RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/../Execution/Release")

if(MSVC)
  target_compile_options(
    MEngine 
    PRIVATE 
    /W4
    /std:c++20
    /FI${CMAKE_CURRENT_SOURCE_DIR}/CoreAPI.h
    )
else()
  # GCC or Clang
  # add_definitions(-include ${CMAKE_CURRENT_SOURCE_DIR}/CoreAPI.h)
endif()

add_subdirectory(Core)
add_subdirectory(Extension)
add_subdirectory(Runtime)
add_subdirectory(Utilities)
add_subdirectory(OTGT)


target_link_libraries(
  MEngine
  Core
  OTGT
)

target_include_directories(
  MEngine
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/Core/Include
  ${CMAKE_CURRENT_SOURCE_DIR}/OTGT/Include
)

add_custom_command(TARGET MEngine POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
          $<TARGET_FILE:Core>
          $<TARGET_FILE:OTGT>
          $<TARGET_FILE_DIR:MEngine>
)