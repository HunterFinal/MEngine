if(ANDROID)
  set(LAUNCH_PLATFORM Android)
elseif(WIN32)
  set_target_properties(MEngine PROPERTIES WIN32_EXECUTABLE ON)
  set(LAUNCH_PLATFORM Windows)
else()
  message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

target_link_libraries(MEngine PRIVATE MEngine.ForceInclude)

file(GLOB_RECURSE LAUNCH_PLATFORM_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/Src/${LAUNCH_PLATFORM}/*.cpp)
file(GLOB_RECURSE LAUNCH_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp)

target_sources(
  MEngine 
  PRIVATE
  ${LAUNCH_SOURCE}
  ${LAUNCH_PLATFORM_SOURCE}
)

target_include_directories(
  MEngine 
  PRIVATE 
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Include
)