// gemaakt door ebbe
// loop functie is regelmatig veranderd door iedereen. meest recente is door robin, gerefactored door ebbe
// setup is door mathias

#include <iostream>
#include <QPoint>
#include "Controller.h"

Controller::Controller(Game &gameModel, CLIView &gameView)
    : gameModel(gameModel), gameView(gameView){
    io = ConsoleIO();
}

void Controller::askCellProcedure(const std::function<bool(QPoint)>& gameFunc) {
    bool validSelection;
    do{
        QPoint cell = io.askCoords(); // vraag
        if(io.exit()) exit(0); // stop als exit request
        validSelection = gameFunc(cell); // voer functie uit en zie of het succes was
    } while(!validSelection); // doe opnieuw als geen succes was
}

void Controller::loop() {
    if(gameModel.isGameOver()) return;

    // Dit is 1 turn:

    gameModel.doubleDobbel(); // genereer nieuwe random keuzes
    for(int move = 0; move <= 1; move++){
        gameView.update();  // teken de view
        bool takeMove = io.askMoveConfirmation();   // vraag om move aan te nemen
        if(!takeMove){
            gameModel.advance();    // skip de move
            continue;
        }
        // vraag de selectie cell
        askCellProcedure([&](QPoint c)->bool{return gameModel.selectPiece(c);});
        gameView.update();
        // vraag de bestemming cell
        askCellProcedure([&](QPoint c)->bool{return gameModel.movePiece(c);});
        gameModel.advance(); // ga verder naar volgende move of turn
    }
}

void Controller::start() {
    setup();
    while(true)
        loop();
}

void Controller::setup() {
    // vraag alle 4 speler namen
    for(int i = 0; i < 4; i++){
        QString name = io.getPlayerName(i + 1);
        gameModel.namePlayer(name, i);
    }
}
