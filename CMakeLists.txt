cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)

project(ecs)

include_directories(
    BEFORE
    ecs/
)

add_library(ecs_module STATIC
    ecs/datastructures/hash.h
    ecs/datastructures/hashmap.h
    ecs/datastructures/sparseset.h
    ecs/Entity.cpp
    ecs/Entity.h
    ecs/IdStorage.cpp
    ecs/IdStorage.h
    ecs/Table.h
    ecs/TableFunctions.cpp
    ecs/Type.h
    ecs/TypeFunctions.cpp
    ecs/World.cpp
    ecs/World.h
    ecs/definitions.h
)

target_link_directories(ecs_module PUBLIC ecs/)

add_executable(ecs)
target_sources(ecs PRIVATE main.cpp)
target_link_libraries(ecs ecs_module)