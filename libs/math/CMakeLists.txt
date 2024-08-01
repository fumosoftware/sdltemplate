cmake_minimum_required(VERSION 3.5)
project(math)

add_library(math src/time.cpp src/shapes/rectangle.cpp)
target_include_directories(math PUBLIC include)
