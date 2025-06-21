cmake_minimum_required(VERSION 3.29.0)

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

target_compile_features(
  Application 
  PRIVATE 
  cxx_std_20
)

# DLL define helper macro
target_compile_definitions(
  Application
  PRIVATE
  APP_DLL_BUILD
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

if(MSVC)
  target_compile_options(
    Application 
    PRIVATE 
    /W4
    /std:c++20
  )
else()
  
endif()

MEngine_setup_target(Application)