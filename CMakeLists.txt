cmake_minimum_required(VERSION 3.20)

project(bastion LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(bastion
    src/main.cpp
    src/Game.cpp
    src/Grid.cpp
    src/Enemy.cpp
    src/Tower.cpp
)

target_include_directories(bastion PRIVATE include)