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
    int move{1};
public:
    void advance();
    [[nodiscard]] Board &getBoard();
    [[nodiscard]] bool isGameOver() const;
    [[nodiscard]] Color getCurrentTurn() const;
    int getCurrentMove() const;
    Player& getCurrentPlayer();
    Dice &getDice();
    Player& getPlayerByColor(Color color);
};



#endif //CHATURAJI_GAMESTATE_H
