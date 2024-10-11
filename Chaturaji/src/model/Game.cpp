

#include <iostream>
#include <ctime>
#include "Game.h"
#include "Piece.h"

Game::Game() : board(), mover(board) {
    currentlySelectedCell = nullptr;
}

const Board& Game::getBoard() const {
    return board;
}
void Game::setCell(QPoint cell, Piece* value) {
    board.setCell(cell, *value);
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

bool Game::selectCell(QPoint cell) {
    /* TODO:
         * if Board.IsEmpty()
         * if Piece.getPlayer != currentPlayer
         * -> return false
         * De rest is wat hieronder al staat, is al goed
     */
    if(currentlySelectedCell != nullptr){
        delete currentlySelectedCell;
    }
    currentlySelectedCell = new QPoint(cell);
    return true;
}

bool Game::moveToDestination(QPoint cell) {
    /* TODO:
         * bool empty = Board.IsEmpty()
         * if !empty && Piece.getPlayer == currentPlayer
         * -> return false
     */
    /* TODO:
        * if empty
        * -> validate via walkpattern
        * ->> als niet goed -> return false
        * else
        * -> validate via attackpattern
        * ->> als niet goed -> return false
        * * De rest is wat hieronder al staat, is al goed
     */
    if(currentlySelectedCell != nullptr){
        delete currentlySelectedCell;
    }
    QPoint fromCell = *currentlySelectedCell;
    currentlySelectedCell = nullptr;
    return true;
}
