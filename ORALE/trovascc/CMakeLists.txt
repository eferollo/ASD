cmake_minimum_required(VERSION 3.24)
project(trovascc C)

set(CMAKE_C_STANDARD 17)

add_executable(trovascc main.c Graph.c Graph.h PQ.c PQ.h)
