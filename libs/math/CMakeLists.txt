cmake_minimum_required(VERSION 3.5)
project(fumomath)

add_library(fumomath src/shapes/rectangle.cpp)
target_include_directories(fumomath PUBLIC include)
