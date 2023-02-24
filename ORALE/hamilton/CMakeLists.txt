cmake_minimum_required(VERSION 3.24)
project(hamilton C)

set(CMAKE_C_STANDARD 17)

add_executable(hamilton main.c Graph.c Graph.h)
