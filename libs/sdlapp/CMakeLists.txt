cmake_minimum_required(VERSION 3.5)
project(sdlapp)

add_library(sdlapp src/sdlapp.cpp)
target_link_libraries(sdlapp PRIVATE SDL3::SDL3)
target_link_libraries(sdlapp PUBLIC math)
target_include_directories(sdlapp PUBLIC include)
