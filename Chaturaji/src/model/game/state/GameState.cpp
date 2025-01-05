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
    do{
        turn++;
    } while(!players[getCurrentTurn()].isAlive());
}

Player &GameState::getCurrentPlayer() {
    return players[getCurrentTurn()];
}
