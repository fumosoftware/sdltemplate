cmake_minimum_required(VERSION 3.5)
project(sdltemplate_events)

add_library(sdltemplate_events src/events/event.cpp)
target_include_directories(sdltemplate_events PUBLIC include)
