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

MEngine_setup_target(Core)

