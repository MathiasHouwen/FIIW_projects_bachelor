//
// Created by ebbew on 7-10-2024.
//
#include <iostream>
#include "Controller.h"

Controller::Controller(const Game &gameModel, const GameView &gameView)
    : gameModel(gameModel), gameView(gameView){
    io = ConsoleIO();
}

bool Controller::update() {
    ConsoleIO console{};

    if(console.exit()){
        return !console.exit();
    }
    //model update
    //model.???()
    //view update
    gameView.printBoard();

    //exit condition
    // bool exit = command == 'Q' || command == 'q';
    // return !exit;
}

void Controller::startGameLoop() {
    std::cout << "enter any character to start" << std::endl;
    while(true){
        bool continueLoop = update();

        if(!continueLoop) break;
    }
}
