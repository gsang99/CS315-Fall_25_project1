cmake_minimum_required(VERSION 4.0)
project(CS315_project1)

set(CMAKE_CXX_STANDARD 20)

add_executable(CS315_project1 main.cpp
        CS315_maze.cpp
        CS315_maze.h
        cmake-build-debug/maze.txt)
