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

add_executable(sdltemplate src/main.cpp)

target_link_libraries(sdltemplate PRIVATE SDL3::SDL3 fmt)

