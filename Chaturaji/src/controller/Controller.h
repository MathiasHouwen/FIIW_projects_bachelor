//
// Created by ebbew on 7-10-2024.
//

#ifndef CHATURAJI_CONTROLLER_H
#define CHATURAJI_CONTROLLER_H


#include "../view/GameView.h"
#include "ConsoleIO.h"

class Controller {
private:
    Game& gameModel;
    GameView& gameView;
    bool update();
    ConsoleIO io;
    void gameSetup();
public:
    Controller(Game &gameModel, GameView &gameView);
    void startGameLoop();
};


#endif //CHATURAJI_CONTROLLER_H
