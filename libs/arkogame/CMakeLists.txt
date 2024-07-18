cmake_minimum_required(VERSION 3.5)
project(arkogame)


add_library(arkogame src/arkogame/arkogame.cpp)
target_include_directories(arkogame PUBLIC include)
target_link_libraries(arkogame PUBLIC sdltemplate_events)
