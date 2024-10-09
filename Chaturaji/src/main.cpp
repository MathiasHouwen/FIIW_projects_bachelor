#include <QCoreApplication>
#include <iostream>
#include "view/GameView.h"
#include "model/Game.h"
#include "controller/Controller.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Game model;
    GameView view(model);
    Controller controller(model, view);
    controller.startGameLoop();
    QCoreApplication::quit();
    return 0;
}
