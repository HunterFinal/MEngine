cmake_minimum_required(VERSION 3.33.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(MEngine VERSION 0.1.0 LANGUAGES C CXX)

# Add global macro definition
add_compile_definitions(
  UNICODE=1
  _UNICODE=1
)

if(MSVC)
  add_compile_options(
    /std:c++latest
    /W4)
else()
  # GCC or Clang?
endif()

add_subdirectory(Framework)
add_subdirectory(Game)
