

#include "Game.h"

Game::Game() : board() {}

const Board& Game::getBoard() const {
    return board;
}
void Game::setCell(int row, int col, bool value) {
    board.setCell(row, col, value);
}