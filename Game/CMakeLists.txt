cmake_minimum_required(VERSION 3.29.0)

file(GLOB_RECURSE Game_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp)

add_library(
  Game 
  SHARED 
  ${Game_SOURCES} 
)

target_compile_features(
  Game 
  PRIVATE 
  cxx_std_20
)

# DLL define helper macro
target_compile_definitions(
  Game
  PRIVATE
  GAME_DLL_BUILD
  APP_DLL_BUILD
)

target_include_directories(
  Game 
  PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

target_link_libraries(
  Game
  PRIVATE
  APP
)


if(MSVC)
  target_compile_options(
    Game 
    PRIVATE 
    /W4
    /std:c++20
    /FI${CMAKE_SOURCE_DIR}/Framework/CoreAPI.h
  )
else()
  
endif()

target_link_libraries(
  Game
  PRIVATE
  APP
  Core
)
