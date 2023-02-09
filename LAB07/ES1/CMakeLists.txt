cmake_minimum_required(VERSION 3.24)
project(ES1 C)

set(CMAKE_C_STANDARD 17)

add_executable(ES1 equipArray.h inv.h invArray.h pg.h pgList.h gdr.c inv.c equipArray.c invArray.c pg.c pgList.c)
