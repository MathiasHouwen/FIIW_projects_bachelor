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
    ConsoleIO io;

    void loop();    // game loop
    void setup();   // initele game setup

    // vraagt een cell en gebruikt deze voor een game functie
    // indien ongeldig, vraagt opnieuw
    // indien het antwoord een exit request was, stopt de app ook
    void askCellProcedure(const std::function<bool(QPoint)>& gameFunc);
public:
    Controller(Game &gameModel, GameView &gameView);
    void start(); // roept setup en loop aan
};


#endif //CHATURAJI_CONTROLLER_H
