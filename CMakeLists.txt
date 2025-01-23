cmake_minimum_required(VERSION 3.28)
project(oving2)

set(CMAKE_CXX_STANDARD 17)

add_executable(oving2 main.cpp
        Workers.cpp
        Workers.h)
