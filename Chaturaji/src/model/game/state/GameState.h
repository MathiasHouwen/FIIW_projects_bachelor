//
// Created by ebbew on 5-1-2025.
//

#ifndef CHATURAJI_GAMESTATE_H
#define CHATURAJI_GAMESTATE_H


#include "Board.h"
#include "identities/Player.h"
#include "Dice.h"

class GameState {
private:
    Board board;
    QHash<Color, Player> players;
    Dice dice;
    bool gameOver;
    int turn{0};
public:
    void advance();
    const Board &getBoard() const;
    [[nodiscard]] bool isGameOver() const;
    [[nodiscard]] Color getCurrentTurn() const;
};


#endif //CHATURAJI_GAMESTATE_H
