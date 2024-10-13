#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include "view/GameView.h"
#include "model/Game.h"
#include "controller/Controller.h"
#include "controller/FileIO.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Game model;

    // TEST ========================

    Board& board = model.getBoard();
    board.setCell({2,4}, {Piece::Type::ELEPH, {0,1}, model.getCurrentPlayer()});
    board.setCell({4,2}, {Piece::Type::BOAT, {0,1}, model.getCurrentPlayer()});
    Player other(Player::colour::GREEN);
    board.setCell({6,4}, {Piece::Type::PAWN, {0,-1}, other});

    // Test code for Piece to JSON
//    Piece testPiece{Piece::Type::ELEPH, {0,1}, model.getCurrentPlayer()};
//    QJsonObject JsonObjPeice = FileIO::pieceToJson(&testPiece);
//    QJsonDocument jsonDoc(JsonObjPeice);
//    QByteArray jsonString = jsonDoc.toJson();
//    std::cout << jsonString.toStdString() << std::endl;

//    QJsonDocument doc = FileIO::generateJSONfile(&board);
//    QByteArray jsonString = doc.toJson();
//    std::cout << jsonString.toStdString() << std::endl;
    // TEST ========================

    GameView view(model);
    Controller controller(model, view);
    controller.start();
    QCoreApplication::quit();
    return 0;
}