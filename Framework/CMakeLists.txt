cmake_minimum_required(VERSION 3.29.0)

# use this BEFORE project()
# can not generate compile_commands.json when using MSVC,
# use Ninja to generate
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# project(MEngine VERSION 0.1.0 LANGUAGES C CXX)

add_executable(
  MEngine 
  WIN32 
  ${CMAKE_CURRENT_SOURCE_DIR}/EntryPoint.cpp
)

target_compile_features(
  MEngine 
  PRIVATE 
  cxx_std_20
)

# Debug/Release specific macro
function(MEngine_setup_target target)
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(
      ${target}
      PUBLIC
      ME_DEBUG_ON=1
    )
  elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(
      ${target}
      PUBLIC
      ME_RELEASE_ON=1
    )
  endif()
endfunction()

set_target_properties(
  MEngine
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/Execution/Debug"
  RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/Execution/Release")

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
add_subdirectory(Extensions)
add_subdirectory(Runtime)
add_subdirectory(Utilities)
add_subdirectory(OTGT)
add_subdirectory(Application)
add_subdirectory(ThirdParty/spdlog)

# Dependency
target_link_libraries(
  MEngine
  PRIVATE
  Core
  OTGT
  Game
  Application
)

# Modules
target_include_directories(
  MEngine
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/Core
  ${CMAKE_CURRENT_SOURCE_DIR}/Core/Include
  ${CMAKE_CURRENT_SOURCE_DIR}/OTGT
  ${CMAKE_CURRENT_SOURCE_DIR}/OTGT/Include
  ${CMAKE_CURRENT_SOURCE_DIR}/Application
  ${CMAKE_CURRENT_SOURCE_DIR}/Application/Include
)

# Libraries include
target_include_directories(
  MEngine
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/spdlog/include
)

# dll copy
add_custom_command(TARGET MEngine POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
          $<TARGET_FILE:Core>
          $<TARGET_FILE:OTGT>
          $<TARGET_FILE:Game>
          $<TARGET_FILE_DIR:MEngine>
)