cmake_minimum_required(VERSION 3.24)
project(ES1 C)

set(CMAKE_C_STANDARD 17)

add_executable(ES1 main.c Graph.c Graph.h ST.c ST.h Item.c Item.h)
