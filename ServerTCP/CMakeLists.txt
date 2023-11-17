cmake_minimum_required(VERSION 3.26)
project(ServerTCP C)

set(CMAKE_C_STANDARD 17)

#link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(ServerTCP main.c
        serverInit.c
        serverInit.h
        driver_lib.h
        driver_lib.c)

#target_link_libraries(ServerTCP ${CMAKE_SOURCE_DIR}/libdriver_lib.a)

