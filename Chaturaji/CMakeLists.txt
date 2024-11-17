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
        src/model/game/Game.h
        src/model/game/Game.cpp
#        src/view/CLIView.h
#        src/controller/ConsoleIO.h
#        src/controller/ConsoleIO.cpp
#        src/view/CLIView.cpp
        src/model/game/board/Board.h
        src/model/game/board/Board.cpp
#        src/controller/CLI_Controller.h
#        src/controller/CLI_Controller.cpp
        src/model/logic/PatternMover.h
        src/model/logic/PatternMover.cpp
        src/model/game/board/Piece.h
        src/model/game/board/Piece.cpp
        src/model/game/Player.cpp
        src/model/game/Player.h
        src/model/game/Player.h
        src/model/io/FileIO.cpp
        src/model/io/FileIO.h
        src/model/io/FileIO.h
        src/model/logic/Pattern.h
        src/view/mainscreen/MainWindow.cpp
        src/view/mainscreen/MainWindow.h
        src/view/mainscreen/mainwindow.ui
        src/view/mainscreen/board/SquareView.cpp
        src/view/mainscreen/board/SquareView.h
        src/view/mainscreen/board/BoardView.cpp
        src/view/mainscreen/board/BoardView.h
        src/view/mainscreen/board/PieceWidgit.cpp
        src/view/mainscreen/board/PieceWidgit.h
        src/view/mainscreen/player/PlayerView.cpp
        src/view/mainscreen/player/PlayerView.h
        src/view/mainscreen/player/PlayerView.h
        src/view/mainscreen/toolbar/FileIOView.cpp
        src/view/mainscreen/toolbar/FileIOView.h
        src/view/mainscreen/toolbar/FileIOView.h
        src/controller/Controller.cpp
        src/controller/Controller.h
        src/controller/Controller.h
        src/model/game/Dice.cpp
        src/model/game/Dice.h
        src/view/mainscreen/moves/DieView.cpp
        src/view/mainscreen/moves/DieView.h
        src/view/mainscreen/moves/DiceAndMovesView.cpp
        src/view/mainscreen/moves/DiceAndMovesView.h
        src/view/startscreen/startscreen.cpp
        src/view/startscreen/startscreen.h
        src/view/startscreen/startscreen.ui
        src/view/mainscreen/player/PlayersView.cpp
        src/view/mainscreen/player/PlayersView.h
)
target_link_libraries(Chaturaji Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::SvgWidgets Qt${QT_VERSION_MAJOR}::Xml)

include(GNUInstallDirs)
install(TARGETS Chaturaji
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
