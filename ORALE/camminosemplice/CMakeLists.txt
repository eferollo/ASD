cmake_minimum_required(VERSION 3.24)
project(camminosemplice C)

set(CMAKE_C_STANDARD 17)

add_executable(camminosemplice main.c Graph.c Graph.h PQ.c PQ.h)
