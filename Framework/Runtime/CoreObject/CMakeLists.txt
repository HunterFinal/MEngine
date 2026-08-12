file(GLOB_RECURSE COREOBJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp)

add_library(
  CoreObject 
  SHARED 
  ${COREOBJECT_SOURCES} 
)

target_link_libraries(
  CoreObject
  PUBLIC
  Core
)

target_include_directories(
  CoreObject
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

# DLL define helper macro
target_compile_definitions(
  CoreObject
  PRIVATE
  COREOBJECT_EXPORT
)

target_include_directories(
  CoreObject 
  PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

target_include_directories(
  CoreObject
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/Internal
)

MEngine_setup_target(CoreObject)

