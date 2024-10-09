cmake_minimum_required(VERSION 3.29)
project(my_own_db C)

set(CMAKE_C_STANDARD 11)

add_executable(my_own_db
        src/main.c
        src/repl/inputs.c
        src/repl/inputs.h)
