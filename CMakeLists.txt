cmake_minimum_required(VERSION 3.6)
project(PgmReader)

set(SOURCE_FILES main.c pgm.c pgm.h)
add_executable(PgmReader ${SOURCE_FILES})