cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)

project(ecs)

include_directories(
    BEFORE
    ecs/
)

add_library(ecs_module STATIC
    ecs/Hash.hpp
    ecs/Definitions.hpp
    ecs/IdStorage.cpp
    ecs/IdStorage.hpp
    ecs/Table.hpp
    ecs/Type.hpp
    ecs/World.cpp
    ecs/World.hpp
)

target_link_directories(ecs_module PUBLIC ecs/)

add_executable(ecs)
target_sources(ecs PRIVATE main.cpp)
target_link_libraries(ecs ecs_module)