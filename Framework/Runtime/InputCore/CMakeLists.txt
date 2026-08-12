file(GLOB_RECURSE PRIVATE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp)
file(GLOB_RECURSE INTERNAL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Internal/*.cpp)

set( 
  SRCS 
  ${PRIVATE_SOURCES}
  ${INTERNAL_SOURCES}
)


file(GLOB_RECURSE INPUT_CORE_SOURCE CONFIGURE_DEPENDS ${SRCS})

add_library(
  InputCore
  SHARED
  ${INPUT_CORE_SOURCE}
)

target_link_libraries(
  InputCore
  PRIVATE
  Core
)

target_compile_definitions(
  InputCore
  PRIVATE
  INPUT_CORE_DLL_BUILD
)

target_include_directories(
  InputCore
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Include  
  PRIVATE
  ${CMAKE_SOURCE_DIR}/Framework/Core 
  ${CMAKE_SOURCE_DIR}/Framework/Core/Include
  ${CMAKE_CURRENT_SOURCE_DIR}/Internal
)

MEngine_setup_target(InputCore)