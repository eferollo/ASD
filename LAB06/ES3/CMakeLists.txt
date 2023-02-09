cmake_minimum_required(VERSION 3.24)
project(ES3 C)

set(CMAKE_C_STANDARD 17)

add_executable(ES3 gdr.c inv.h invArray.h pg.h pgList.h equipArray.h inv.c invArray.c pg.c pgList.c equipArray.c invArray.c)
