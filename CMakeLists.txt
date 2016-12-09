cmake_minimum_required(VERSION 3.0)
project(PgmReader)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -ggdb")

set(SOURCE_FILES main.c pgm.c pgm.h)
add_executable(PgmReader ${SOURCE_FILES})
