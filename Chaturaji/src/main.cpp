#include <QCoreApplication>
#include <QDebug>

#include "view/GameView.h"
#include "model/Board.h"
#include "model/Game.h"

#include "./view/GameView.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    const Board board{};
    const Game game{};
    GameView view(board, game);
    view.printBoard();
    return QCoreApplication::exec();
}
