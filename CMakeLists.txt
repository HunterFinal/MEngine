cmake_minimum_required(VERSION 3.29.0)

project(MEngine VERSION 0.1.0 LANGUAGES C CXX)

# Add global macro definition
add_compile_definitions(
  UNICODE=1
  _UNICODE=1
)

add_subdirectory(Framework)
add_subdirectory(Game)
