#ifndef CHATURAJI_GAMEVIEW_H
#define CHATURAJI_GAMEVIEW_H

#include "../model/Board.h"
#include "../model/Game.h"

class GameView {
private:
    Board gameBoard;
    // player turn
    // ...?
public:
    explicit GameView(const Game &game);
    void printBoard();
};

#endif //CHATURAJI_GAMEVIEW_H
