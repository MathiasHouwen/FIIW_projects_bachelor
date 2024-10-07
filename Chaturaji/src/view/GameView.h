#ifndef CHATURAJI_GAMEVIEW_H
#define CHATURAJI_GAMEVIEW_H

#include "../model/Board.h"
#include "../model/Game.h"

class GameView {
private:
    Board board;
    Game game;
public:
    GameView(const Board &board, const Game &game)
        : board(board),
          game(game) {
    }

    void printBoard();
};

#endif //CHATURAJI_GAMEVIEW_H
