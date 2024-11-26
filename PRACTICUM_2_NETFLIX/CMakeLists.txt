cmake_minimum_required(VERSION 3.5.0)
project(PRACTICUM_2_NETFLIX)
include(FetchContent)

FetchContent_Declare(
        csv-parser
        GIT_REPOSITORY git@github.com:vincentlaucsb/csv-parser.git
        GIT_TAG        105b44d819a37d9329df16ca4417c3b3f6c2ad98 # release 2.3.0
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-profile-arcs -fno-test-coverage")
set(CMAKE_CXX_STANDARD 20)

add_executable(PRACTICUM_2_NETFLIX src/main.cpp
        src/Trie.cpp
        src/Trie.h
        src/modules/CLI.cpp
        src/modules/CLI.h
        src/utils/netflixCLI.cpp
        src/utils/netflixCLI.h
        src/Pool.cpp
        src/Pool.h
        src/YearMap.cpp
        src/YearMap.h
        src/MovieOrShow.cpp
        src/MovieOrShow.h
        src/Netflix.cpp
        src/Netflix.h
        src/MovieOrShowPool.cpp
        src/MovieOrShowPool.h
        src/utils/CSVHandler.cpp
        src/utils/CSVHandler.h)

FetchContent_MakeAvailable(csv-parser)
target_link_libraries(PRACTICUM_2_NETFLIX PRIVATE csv)
target_link_libraries(PRACTICUM_2_NETFLIX PRIVATE gcov)

