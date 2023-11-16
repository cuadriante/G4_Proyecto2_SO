cmake_minimum_required(VERSION 3.26)
project(ClientTCP C)

set(CMAKE_C_STANDARD 11)

add_executable(ClientTCP main.c
        client.c
        client.h
        clientCLI.c
        clientCLI.h
        chacha20.h
        chacha20.c
)
