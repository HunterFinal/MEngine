cmake_minimum_required(VERSION 3.29.0)

# use this BEFORE project()
# can not generate compile_commands.json when using MSVC,
# use Ninja to generate
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# Container to cache all module names
set_property(GLOBAL PROPERTY MODULE_NAMES "")
function(register_module_manifest TARGET_NAME)
  set_property(GLOBAL APPEND PROPERTY MODULE_NAMES "${TARGET_NAME}")
endfunction()

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

function(MEngine_setup_target target)
  # Debug/Release specific macro
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

  # Generate manifest for the target
  register_module_manifest(${target})

  # Generate dynamic module predefined name macro
  target_compile_definitions(
    ${target}
    PRIVATE
    PREDEFINED_MODULE_NAME="${target}"
  )
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
add_subdirectory(OpenGLDriver)
add_subdirectory(OTGT)
add_subdirectory(RHI)
add_subdirectory(Runtime)
add_subdirectory(Utilities)
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
  FutureFlexCore
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
  ${CMAKE_CURRENT_SOURCE_DIR}/Runtime
  ${CMAKE_CURRENT_SOURCE_DIR}/Runtime/Include
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
          $<TARGET_FILE:Application>
          $<TARGET_FILE:InputCore>
          $<TARGET_FILE:RHI>
          $<TARGET_FILE:FutureFlexCore>
          $<TARGET_FILE_DIR:MEngine>
)

# Generate module manifest
get_property(ALL_MODULES GLOBAL PROPERTY MODULE_NAMES)

set(JSON_ENTRIES "")

# Append all module info and add ',' between each(ignore last one)
foreach(Module ${ALL_MODULES})
  list(APPEND JSON_ENTRIES "    \"${Module}\": \"$<TARGET_FILE_NAME:${Module}>\"")
endforeach()
list(JOIN JSON_ENTRIES ",\n" MODULE_CONTENT)
set(MODULE_MANIFEST "{\n  \"Modules\":\n  {\n${MODULE_CONTENT}\n  }\n}")

# Create manifest file
# Default encoding : UTF-8
file(GENERATE
     OUTPUT "$<TARGET_FILE_DIR:MEngine>/ModuleManifest.manifest"
     CONTENT "${MODULE_MANIFEST}"
)

# Copy all module 
foreach(Module ${ALL_MODULES})
  add_custom_command(TARGET MEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:${Module}>
            $<TARGET_FILE_DIR:MEngine>
    )
endforeach()

MEngine_setup_target(MEngine)


