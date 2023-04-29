cmake_minimum_required(VERSION 3.22)
project(SGE)

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(examples/dev examples/dev)
add_subdirectory(examples/collision_phase examples/collision_phase)
add_subdirectory(examples/scenes examples/scenes)