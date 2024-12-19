cmake_minimum_required(VERSION 3.27.8)
project(PRACTICUM_3_ZOOMNET)

set(CMAKE_CXX_STANDARD 23)

add_executable(PRACTICUM_3_ZOOMNET
    main.cpp
        src/graph/Graph.h
        src/graph/Graph.cpp
        src/modules/CLI.cpp
        src/modules/CLI.h
        src/modules/CommandParser.cpp
        src/modules/CommandParser.h
        src/utils/ZoomNetCLI.cpp
        src/utils/ZoomNetCLI.h
        src/ZoomNet.cpp
        src/ZoomNet.h
        src/graph/GraphStructs.h
        src/utils/namedObjectLUT.h
        src/utils/namedObjectLUT.cpp
        src/graph/GraphStructs.cpp
        src/ZoomNetGraph.cpp
        src/ZoomNetGraph.h
)
