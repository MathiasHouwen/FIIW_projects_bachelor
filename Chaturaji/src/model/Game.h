#ifndef CHATURAJI_GAME_H
#define CHATURAJI_GAME_H


#include "Board.h"

class Game {
private:
    Board board;
public:
    Game();
    const Board& getBoard() const;
    void setCell(QPoint cell, bool value);
};


#endif //CHATURAJI_GAME_H
