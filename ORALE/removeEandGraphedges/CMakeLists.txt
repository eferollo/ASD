cmake_minimum_required(VERSION 3.24)
project(removeEandGraphedges C)

set(CMAKE_C_STANDARD 17)

add_executable(removeEandGraphedges main.c Graph.c Graph.h)
