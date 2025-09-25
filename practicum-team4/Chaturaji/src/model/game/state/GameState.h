//practicum 3:
// - Ebbe: class gemaakt, copy paste van de oude Game class
// - Robin: addbot gemaakt toen we nog de oude game class hadden
// doel: logica decouplen van Game

#ifndef CHATURAJI_GAMESTATE_H
#define CHATURAJI_GAMESTATE_H

#include "Board.h"
#include "identities/Player.h"
#include "Dice.h"
#include "../bots/MoveStrategy.h"

class GameState {
private:
    Board board;
    QHash<Color, Player*> players;
    Dice dice;
    bool gameOver;
    int turn{0};
    int move{1};
    QPair<Color, HomeBoardSide> getAvialableColorAndSide();
public:
    void advance();
    [[nodiscard]] Board &getBoard();
    [[nodiscard]] bool isGameOver() const;
    [[nodiscard]] Color getCurrentTurn() const;
    int getCurrentMove() const;
    Player* getCurrentPlayer();
    Dice &getDice();
    Player* getPlayerByColor(Color color);
    void addPlayer(QString name);
    void addBot(QString name, std::shared_ptr<MoveStrategy> strategy);
    void addPlayer(Player player);
    void clearPlayers();
};



#endif //CHATURAJI_GAMESTATE_H
