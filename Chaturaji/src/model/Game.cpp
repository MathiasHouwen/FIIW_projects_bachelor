

#include <iostream>
#include <ctime>
#include "Game.h"
#include "Piece.h"

Game::Game() : board(), mover(board) {
}

const Board& Game::getBoard() const {
    return board;
}
void Game::setCell(QPoint cell, bool value) {
    board.setCell(cell, value);
}

QPair<int, int> Game::doubleDobbel() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int die1 = std::rand() % 6 + 1;
    int die2 = std::rand() % 6 + 1;
    return QPair<int, int>(die1, die2);  ;
}

void Game::initPlayers(QString *players) {

    Player::colour colours[4] = {
            Player::colour::RED,
            Player::colour::BLUE,
            Player::colour::GREEN,
            Player::colour::YELLOW
    };

    for (int i = 0; i < 4; ++i) {
        QString playerName = players[i];
        Player player{playerName, colours[i]};
    }
}