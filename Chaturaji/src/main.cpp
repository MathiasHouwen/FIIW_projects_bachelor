#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QApplication>
#include "view/GameView.h"
#include "model/Game.h"
#include "controller/Controller.h"
#include "controller/FileIO.h"
#include "view/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
//    Game model{};
//    GameView view(model);
//    Controller controller(model, view);
//
//    FileIO io{"../startingFile.txt"};
//    io.loadBoard(&model);
//
//    controller.start();
    return app.exec();
}