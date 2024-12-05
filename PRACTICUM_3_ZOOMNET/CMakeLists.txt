cmake_minimum_required(VERSION 3.27.8)
project(PRACTICUM_3_ZOOMNET)

set(CMAKE_CXX_STANDARD 20)

add_executable(PRACTICUM_3_ZOOMNET
    main.cpp
        Graph.h
        Graph.cpp
        modules/CLI.cpp
        modules/CLI.h
        modules/CommandParser.cpp
        modules/CommandParser.h
        utils/ZoomNetCLI.cpp
        utils/ZoomNetCLI.h)
