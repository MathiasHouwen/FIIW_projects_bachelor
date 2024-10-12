#ifndef CHATURAJI_GAME_H
#define CHATURAJI_GAME_H


#include "Board.h"
#include "PatternMover.h"
#include "Player.h"

class Game {
private:
    Board board;
    PatternMover mover;
    Player players[4] = {{Player::colour::RED}, {Player::colour::GREEN}, {Player::colour::BLUE}, {Player::colour::YELLOW}};
    QPoint* currentlySelectedCell;
    QPair<int, int> dice;
    int move{0};    // 1ste of 2de piece van de 2 dobbelstenen
    int turn{0};    // player beurt
    bool gameOver{false};
public:
    QPoint* getCurrentlySelectedCell() const;
    const QPair<int, int> &getDice() const;
    int getMove() const;
    int getTurn() const;
    QSet<QPoint> getPossibleMoves();
    Game();
    Board& getBoard();
    void doubleDobbel();
    void namePlayer(const QString& name, int playerIndex);
    bool selectPiece(QPoint cell);
    bool movePiece(QPoint destinationCell);
    void advance();
    Player &getCurrentPlayer();
    bool isGameOver() const;
};


#endif //CHATURAJI_GAME_H
