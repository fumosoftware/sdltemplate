cmake_minimum_required(VERSION 3.5)
project(fumocore)

add_library(fumocore src/core/sdlapp/sdlapp.cpp src/core/time/time.cpp src/core/arkogame/components/controllerbody.cpp src/core/arkogame/components/physicsbody.cpp)
target_link_libraries(fumocore PRIVATE SDL3::SDL3)
target_link_libraries(fumocore PUBLIC fumomath)
target_include_directories(fumocore PUBLIC include)
