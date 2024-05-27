cmake_minimum_required(VERSION 3.5)
project(sdltemplate)

find_package(fmt)
if(${fmt_FOUND})
  message(STATUS "the package \"fmt\" has been found")
else()
  message(FATAL_ERROR "could not find package \"fmt\"")
endif()

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
if(${SDL3_FOUND})
  message(STATUS "the package \"SDL3\" has been found")
else()
  message(FATAL_ERROR "could not find package \"SDL3\"")
endif()

find_package(spdlog REQUIRED)
if(${spdlog_FOUND})
  message(STATUS "the package \"spdlog\" has been found")
else()
  message(FATAL_ERROR "could not find package \"spdlog\"")
endif()

add_executable(sdltemplate src/main.cpp src/app_main.cpp src/logging.cpp)

target_link_libraries(sdltemplate PRIVATE SDL3::SDL3 fmt)
target_link_libraries(sdltemplate PRIVATE spdlog::spdlog_header_only)

message("CMake Build Type: ${CMAKE_BUILD_TYPE}")

message("CMAKE DIR: ${CMAKE_SOURCE_DIR}")

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  message(STATUS "creating a symbolic link to build/debug/compile_commands.json")
  file(CREATE_LINK "${CMAKE_SOURCE_DIR}/build/debug/compile_commands.json" "compile_commands.json" COPY_ON_ERROR SYMBOLIC)
elseif("{$CMAKE_BUILD_TYPE}" STREQUAL "Release")
  message(STATUS "creating a symbolic link to build/release/compile_commands.json")
  file(CREATE_LINK "${CMAKE_SOURCE_DIR}/build/release/compile_commands.json" "compile_commands.json" COPY_ON_ERROR SYMBOLIC)
endif()



