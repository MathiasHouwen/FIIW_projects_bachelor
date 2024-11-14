#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QApplication>
#include <QDir>
#include "view/CLIView.h"
#include "model/Game.h"
#include "controller/CLI_Controller.h"
#include "model/FileIO.h"
#include "model/Square.h"
#include "view/MainWindow.h"
#include "view/SquareView.h"
#include "view/PieceWidgit.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();



//    GameView view(model);
//    CLI_Controller controller(model, view);
//
//
//
//    controller.start();
    return app.exec();
}