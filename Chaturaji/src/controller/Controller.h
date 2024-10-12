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
    void loop();
    ConsoleIO io;
    void setup();
    void askCellProcedure(const std::function<void(QPoint)>& gameFunc);
public:
    Controller(Game &gameModel, GameView &gameView);
    void start();
};


#endif //CHATURAJI_CONTROLLER_H
