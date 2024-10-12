//
// Created by ebbew on 7-10-2024.
//
#include <iostream>
#include <QPoint>
#include "Controller.h"
#include "../model/Piece.h"

Controller::Controller(Game &gameModel, GameView &gameView)
    : gameModel(gameModel), gameView(gameView){
    io = ConsoleIO();
}

void Controller::askCellProcedure(const std::function<bool(QPoint)>& gameFunc) {
    bool validSelection;
    do{
        QPoint cell = io.getCords();
        if(io.exit()) exit(0);
        validSelection = gameFunc(cell);
    } while(!validSelection);
}

void Controller::loop() {
    askCellProcedure([&](QPoint c)->bool{return gameModel.selectPiece(c);});
    askCellProcedure([&](QPoint c)->bool{return gameModel.movePiece(c);});
    gameView.printBoard();
}

void Controller::start() {
    setup();
    gameView.printBoard();
    while(true)
        loop();
}

void Controller::setup() {
    for(int i = 0; i < 4; i++){
        QString name = io.getPlayerName(i + 1);
        gameModel.namePlayer(name, i);
    }
}
