file(GLOB_RECURSE OTGT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp)

add_library(
  OTGT 
  SHARED 
  ${OTGT_SOURCES} 
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
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

MEngine_setup_target(OTGT)