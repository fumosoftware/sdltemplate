cmake_minimum_required(VERSION 3.5)
project(sdlapp)

add_library(sdlapp src/sdlapp.cpp)
target_link_libraries(sdlapp PRIVATE SDL3::SDL3)
target_include_directories(sdlapp PUBLIC include)
