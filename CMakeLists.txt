
cmake_minimum_required(VERSION 3.25)

project(waster)

set(CMAKE_C_STANDARD 11)

add_executable(waster

        src/waster.c
        src/config.h
        src/str.c
        src/scan.c
        src/scan.h

)

