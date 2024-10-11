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
    Player player("Test", Player::colour::RED);

    bool validSelection;
    do{
        QPoint fromCell = io.getCords();
        if(io.exit()) return false;
        validSelection = true; // game.select
    } while(validSelection);
    QPoint toCell;
    do{
        toCell = io.getCords();
        if(io.exit()) return false;
        validSelection = true; // game.is...
    } while(validSelection);

    gameView.printBoard();
    return true;
}

void Controller::startGameLoop() {
    //std::cout << "enter any character to start" << std::endl;
    gameView.printBoard();
    while(true){
        bool continueLoop = update();

        if(!continueLoop) break;
    }
}
