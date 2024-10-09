//
// Created by ebbew on 7-10-2024.
//
#include <iostream>
#include <QPoint>
#include "Controller.h"

Controller::Controller(Game &gameModel, GameView &gameView)
    : gameModel(gameModel), gameView(gameView){
    io = ConsoleIO();
}

bool Controller::update() {
    ConsoleIO console{};
    QPoint point = console.getCords();
    if(console.exit()){
        return !console.exit();
    }
    gameModel.setCell(point, true);
    gameView.printBoard();
    return true;
    //exit condition
    // bool exit = command == 'Q' || command == 'q';
    // return !exit;
}

void Controller::startGameLoop() {
    //std::cout << "enter any character to start" << std::endl;
    gameView.printBoard();
    while(true){
        bool continueLoop = update();

        if(!continueLoop) break;
    }
}
