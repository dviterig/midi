cmake_minimum_required(VERSION 3.16.3)

project(midi VERSION 0.1)

set(CMAKE_C_COMPILER "gcc")

add_compile_options(-Wall -Werror -Wextra)

set(EXECUTABLE midi_controller)
add_executable(${EXECUTABLE} main.c)