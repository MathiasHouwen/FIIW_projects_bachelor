#ifndef CHATURAJI_GAME_H
#define CHATURAJI_GAME_H


#include "Board.h"
#include "PatternMover.h"
#include "Player.h"

class Game {
private:
    Board board;
    PatternMover mover;
    Player players[4];
    QPoint* currentlySelectedCell;
public:
    Game();
    const Board& getBoard() const;
    void setCell(QPoint cell, bool value);
    QPair<int, int> doubleDobbel();
    void initPlayers(QString players[4]);
    bool selectCell(QPoint cell);
    bool moveToDestination(QPoint cell);
};


#endif //CHATURAJI_GAME_H
