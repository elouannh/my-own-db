cmake_minimum_required(VERSION 3.29)
project(my_own_db C)

set(CMAKE_C_STANDARD 11)

add_executable(my_own_db
    main.c
        repl/inputs.c
        repl/inputs.h)
