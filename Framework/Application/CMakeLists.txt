file(GLOB_RECURSE PRIVATE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp)
file(GLOB_RECURSE INTERNAL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Internal/*.cpp)

set(
  APP_SOURCES 
  ${PRIVATE_SOURCES}
  ${INTERNAL_SOURCES}
)

add_library(
  Application 
  SHARED 
  ${APP_SOURCES} 
)

target_link_libraries(
  Application
  PRIVATE
  Core
)

target_include_directories(
  Application
  PRIVATE
  ${PROJECT_SOURCE_DIR}/Framework/Core
  ${PROJECT_SOURCE_DIR}/Framework/Core/Include
)

# DLL define helper macro
target_compile_definitions(
  Application
  PRIVATE
  APP_EXPORT
)

target_include_directories(
  Application 
  PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

target_include_directories(
  Application
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/Internal
)

MEngine_setup_target(Application)