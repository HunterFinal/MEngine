file(GLOB_RECURSE Game_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp)

add_library(
  Game 
  SHARED 
  ${Game_SOURCES} 
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

if(MSVC)
  target_compile_options(
    Game 
    PRIVATE 
    /FI${CMAKE_SOURCE_DIR}/Framework/CoreAPI.h
  )
else()
  
endif()

target_link_libraries(
  Game
  PRIVATE
  Application
  Core
)
