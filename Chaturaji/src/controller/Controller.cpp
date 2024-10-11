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
    ConsoleIO console{};
    if(console.exit()) return !console.exit();

    bool validSelection;
    do{
        QPoint fromCell = io.getCords();
        if(io.exit()) return false;
        validSelection = true; // game.select
    } while(validSelection);
    do{
        QPoint toCell = io.getCords();
        if(io.exit()) return false;
        validSelection = true; // game.moveto
    } while(validSelection);

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
        players[i] = io.getPlayerName(i + 1);
    }
    gameModel.initPlayers(players);

    // LOAD BOARD
}
