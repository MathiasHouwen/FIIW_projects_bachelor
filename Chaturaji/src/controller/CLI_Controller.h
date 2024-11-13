//
// Created by ebbew on 7-10-2024.
//

#ifndef CHATURAJI_CLI_CONTROLLER_H
#define CHATURAJI_CLI_CONTROLLER_H


#include "../view/CLIView.h"
#include "ConsoleIO.h"

class CLI_Controller {
private:
    Game& gameModel;
    CLIView& gameView;
    ConsoleIO io;

    void loop();    // game loop
    void setup();   // initele game setup

    // vraagt een cell en gebruikt deze voor een game functie
    // indien ongeldig, vraagt opnieuw
    // indien het antwoord een exit request was, stopt de app ook
    void askCellProcedure(const std::function<bool(QPoint)>& gameFunc);
public:
    CLI_Controller(Game &gameModel, CLIView &gameView);
    void start(); // roept setup en loop aan
};


#endif //CHATURAJI_CLI_CONTROLLER_H
