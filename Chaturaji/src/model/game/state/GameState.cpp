//
// Created by ebbew on 5-1-2025.
//

#include "GameState.h"

const Board &GameState::getBoard() const {
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
