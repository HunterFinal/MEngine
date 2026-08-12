file(GLOB_RECURSE RHI_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp)

if (WIN32)
  add_subdirectory(Internal/Windows)
endif()

add_library(
  RHI 
  SHARED 
  ${RHI_SOURCES} 
)

target_link_libraries(
  RHI
  PUBLIC
  Core
  Platform_RHI_Impl
)

# DLL define helper macro
target_compile_definitions(
  RHI
  PRIVATE
  RHI_EXPORT
)

target_include_directories(
  RHI 
  PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

target_include_directories(
  RHI
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/Internal
)

MEngine_setup_target(RHI)

