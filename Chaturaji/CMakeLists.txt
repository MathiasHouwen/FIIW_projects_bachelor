cmake_minimum_required(VERSION 3.16)

project(Chaturaji LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(Chaturaji
        src/main.cpp
        src/model/Game.h
        src/model/Game.cpp
        src/view/GameView.h
        src/controller/ConsoleIO.h
        src/controller/ConsoleIO.cpp
        src/view/GameView.cpp
        src/model/Board.h
        src/model/Board.cpp
        src/controller/Controller.h
        src/controller/Controller.cpp
        src/model/PatternMover.h
        src/model/PatternMover.cpp
)
target_link_libraries(Chaturaji Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS Chaturaji
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
