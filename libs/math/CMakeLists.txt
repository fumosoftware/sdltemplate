cmake_minimum_required(VERSION 3.5)
project(arkogame_math)

add_library(arkogame_math src/math/shapes/rect.cpp)
target_include_directories(arkogame_math PUBLIC include)
