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

bool Controller::update() {
    ConsoleIO console{};
    QPoint point = console.getCords(); //TODO: FIX WITH IO
    if(console.exit()) return !console.exit();


    gameModel.setCell(point, true);
    gameView.printBoard();
    return true;
}

void Controller::startGameLoop() {
    gameSetup();
    gameView.printBoard();
    while(true){
        bool continueLoop = update();

        if(!continueLoop) break;
    }
}

void Controller::gameSetup() {
    QString players[4];
    for(int i = 0; i < 4; i++){
        players[i] = io.getPlayerName();
    }

    // LOAD BOARD
}
