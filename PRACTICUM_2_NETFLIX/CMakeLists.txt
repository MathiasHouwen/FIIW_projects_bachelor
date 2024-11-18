cmake_minimum_required(VERSION 3.27.8)
project(PRACTICUM_2_NETFLIX)

set(CMAKE_CXX_STANDARD 20)

add_executable(PRACTICUM_2_NETFLIX src/main.cpp
        src/modules/CLI.cpp
        src/modules/CLI.h
        src/utils/netflixCLI.cpp
        src/utils/netflixCLI.h)
