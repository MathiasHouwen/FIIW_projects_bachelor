cmake_minimum_required(VERSION 3.16)

project(Chaturaji LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${PROJECT_SOURCE_DIR}/src/view)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Gui SvgWidgets Xml)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Gui SvgWidgets Xml)

add_definitions(-DASSET_PATH="${CMAKE_SOURCE_DIR}/assets")

add_executable(Chaturaji
        src/main.cpp
        src/model/Game.h
        src/model/Game.cpp
        src/view/CLIView.h
        src/controller/ConsoleIO.h
        src/controller/ConsoleIO.cpp
        src/view/CLIView.cpp
        src/model/Board.h
        src/model/Board.cpp
        src/controller/CLI_Controller.h
        src/controller/CLI_Controller.cpp
        src/model/PatternMover.h
        src/model/PatternMover.cpp
        src/model/Piece.h
        src/model/Piece.cpp
        src/model/Player.cpp
        src/model/Player.h
        src/model/Player.h
        src/controller/FileIO.cpp
        src/controller/FileIO.h
        src/controller/FileIO.h
        src/model/Pattern.h
        src/view/MainWindow.cpp
        src/view/MainWindow.h
        src/view/mainwindow.ui
        src/model/Square.cpp
        src/model/Square.h
        src/view/SquareView.cpp
        src/view/SquareView.h
        src/view/BoardView.cpp
        src/view/BoardView.h
        src/view/PieceWidgit.cpp
        src/view/PieceWidgit.h
        src/view/PlayerView.cpp
        src/view/PlayerView.h
        src/view/PlayerView.h
        src/view/FileIOView.cpp
        src/view/FileIOView.h
        src/view/FileIOView.h
        src/controller/Controller.cpp
        src/controller/Controller.h
        src/controller/Controller.h
        src/model/Dice.cpp
        src/model/Dice.h
)
target_link_libraries(Chaturaji Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::SvgWidgets Qt${QT_VERSION_MAJOR}::Xml)

include(GNUInstallDirs)
install(TARGETS Chaturaji
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
