#ifndef CHATURAJI_GAME_H
#define CHATURAJI_GAME_H


#include "Board.h"
#include "PatternMover.h"

class Game {
private:
    Board board;
    PatternMover mover;
public:
    Game();
    const Board& getBoard() const;
    void setCell(QPoint cell, bool value);
    QPair<int, int> doubleDobbel();
};


#endif //CHATURAJI_GAME_H
