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
    QPair<int, int> dice;
    int move{0};    // 1ste of 2de piece van de 2 dobbelstenen
    int turn{0};    // player beurt

public:
    QPoint getCurrentlySelectedCell() const;
    const QPair<int, int> &getDice() const;
    int getMove() const;
    int getTurn() const;
    Game();
    const Board& getBoard() const;
    void doubleDobbel();
    void initPlayers(QString players[4]);
    bool selectPiece(QPoint cell);
    bool movePiece(QPoint destinationCell);
    void advance();
    Player &getCurrentPlayer();
};


#endif //CHATURAJI_GAME_H
