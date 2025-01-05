//
// Created by ebbew on 5-1-2025.
//

#include "GameState.h"

Board &GameState::getBoard() {
    return board;
}

bool GameState::isGameOver() const {
    return gameOver;
}

Color GameState::getCurrentTurn() const {
    Color colors[4] = {Color::BLUE, Color::RED, Color::YELLOW, Color::GREEN};
    return colors[turn];
}

void GameState::advance() {
    move++;
    if(move == 1){
        move = 0;
        int attempts = 0;
        do{
            turn++;
            if(turn == 4) turn = 0;
            attempts++;
            if(attempts > 4){
                gameOver = true;
                break;
            }
        } while(!players[getCurrentTurn()].isAlive());
    }
}

Player &GameState::getCurrentPlayer() {
    return players[getCurrentTurn()];
}

Dice &GameState::getDice() {
    return dice;
}

int GameState::getCurrentMove() const {
    return move;
}

Player &GameState::getPlayerByColor(Color color) {
    return players[color];
}

void GameState::addPlayer(QString name, PlayerType type) {
    Color colors[4] = {Color::BLUE, Color::RED, Color::YELLOW, Color::GREEN};
    for(auto color : colors){
        if(players.contains(color)) continue;
        switch (type) {
            case PlayerType::HUMAN:
                players[color] = Player(color,name);
                break;
//            case PlayerType::PASSIVE_BOT:
//                players[color] = PassiveBot(color,name);
//                break;
//            case PlayerType::AGRESSIVE_BOT:
//                players[color] = PassiveBot(color,name);
//                break;
        }
        break;
    }
}

void GameState::clearPlayers() {
    players.clear();
}

void GameState::addPlayer(Player player) {
    players[player.getColor()] = player;
}
