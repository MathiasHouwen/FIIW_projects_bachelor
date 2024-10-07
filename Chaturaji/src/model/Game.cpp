

#include "Game.h"

Game::Game() {
    board = Board();
}
const Board &Game::getBoard() const {
    return board;
}