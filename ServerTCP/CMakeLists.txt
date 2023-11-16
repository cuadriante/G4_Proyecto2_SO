cmake_minimum_required(VERSION 3.26)
project(ServerTCP C)

set(CMAKE_C_STANDARD 17)

add_executable(ServerTCP main.c
        serverInit.c
        serverInit.h)

target_link_libraries(ServerTCP PRIVATE m)