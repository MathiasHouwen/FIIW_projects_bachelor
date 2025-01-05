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

Player &GameState::getCurrentPlayer() {
    return players[getCurrentTurn()];
}
