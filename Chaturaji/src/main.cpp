#include <QCoreApplication>
#include <iostream>
#include "view/GameView.h"
#include "model/Game.h"
#include "controller/Controller.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Game model;
    std::cout << "Main model\t" << &model  << std::endl;
    std::cout << "Main model->board\t" << &(model.getBoard())  << std::endl;
    GameView view(model);
    Controller controller(model, view);
    controller.startGameLoop();
    QCoreApplication::quit();
    return 0;
}
