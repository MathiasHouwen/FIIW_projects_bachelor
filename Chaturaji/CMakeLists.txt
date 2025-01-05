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
add_definitions(-DSAVES_PATH="${CMAKE_SOURCE_DIR}/Saves")

add_executable(Chaturaji
        src/main.cpp
        #        src/view/CLIView.h
#        src/controller/ConsoleIO.h
#        src/controller/ConsoleIO.cpp
#        src/view/CLIView.cpp
        src/model/game/state/Board.h
        src/model/game/state/Board.cpp
#        src/controller/CLI_Controller.h
#        src/controller/CLI_Controller.cpp
        src/model/game/logic/passive/PossibleMovesCalculator.h
        src/model/game/logic/passive/PossibleMovesCalculator.cpp
        src/model/game/state/identities/Player.cpp
        src/model/game/state/identities/Player.h
        src/model/game/state/identities/Player.h
        src/model/io/FileIO.cpp
        src/model/io/FileIO.h
        src/model/io/FileIO.h
        src/model/game/enums_and_structs/Pattern.h
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
        src/model/game/state/Dice.cpp
        src/model/game/state/Dice.h
        src/view/mainscreen/moves/DieView.cpp
        src/view/mainscreen/moves/DieView.h
        src/view/mainscreen/moves/DiceAndMovesView.cpp
        src/view/mainscreen/moves/DiceAndMovesView.h
        src/view/startscreen/startscreen.cpp
        src/view/startscreen/startscreen.h
        src/view/startscreen/startscreen.ui
        src/view/mainscreen/player/PlayersView.cpp
        src/view/mainscreen/player/PlayersView.h
        src/model/game/oude_garbage/Bot.cpp
        src/model/game/oude_garbage/Bot.h
        src/model/game/logic/BoardQuerier.cpp
        src/model/game/logic/BoardQuerier.h
        src/model/game/enums_and_structs/Color.h
        src/model/game/state/identities/Piece.cpp
        src/model/game/state/identities/Piece.h
        src/model/game/util/SquareDimension.cpp
        src/model/game/util/SquareDimension.h
        src/model/game/enums_and_structs/PieceType.h
        src/model/game/enums_and_structs/HomeBoardSide.h
        src/model/game/logic/passive/SpecialRulesChecker.cpp
        src/model/game/logic/passive/SpecialRulesChecker.h
        src/model/game/enums_and_structs/ClassifiedMove.h
        src/model/game/logic/passive/MovesManager.cpp
        src/model/game/logic/passive/MovesManager.h
        src/model/game/logic/active/SpecialRulesExecutor.cpp
        src/model/game/logic/active/SpecialRulesExecutor.h
        src/model/game/state/GameState.cpp
        src/model/game/state/GameState.h
        src/model/game/Game.cpp
        src/model/game/Game.h
        src/controller/GameController.cpp
        src/controller/GameController.h
)
target_link_libraries(Chaturaji Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::SvgWidgets Qt${QT_VERSION_MAJOR}::Xml)

include(GNUInstallDirs)
install(TARGETS Chaturaji
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
