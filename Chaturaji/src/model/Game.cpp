

#include <iostream>
#include <ctime>
#include "Game.h"
#include "Piece.h"

Game::Game() : board(), mover(board), dice() {
    currentlySelectedCell = nullptr;
}

const Board& Game::getBoard() const {
    return board;
}

void Game::doubleDobbel() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    dice.first = std::rand() % 6 + 1;;
    dice.second = std::rand() % 6 + 1;;
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

bool Game::selectPiece(QPoint cell) {
    if(board.isCellEmpty(cell)) return false;
    Piece piece = *board.getCell(cell);
    if(piece.player != getCurrentPlayer()) return false;

    delete currentlySelectedCell;
    currentlySelectedCell = new QPoint(cell);

    return true;
}

bool Game::movePiece(QPoint destinationCell) {
    bool empty = board.isCellEmpty(destinationCell);
    if(empty) return false;
    Piece destPiece = *board.getCell(destinationCell);
    if(destPiece.player == getCurrentPlayer()) return false;

    QPoint fromCell = *currentlySelectedCell;
    Piece sourcePiece = *board.getCell(fromCell);

    Pattern patt = empty ? sourcePiece.getWalkPattern() : sourcePiece.getAttackPattern();
    QSet<QPoint> moves = mover.getPossibleMoves(patt, fromCell);

    if(!moves.contains(destinationCell)) return false;
    board.move(fromCell, destinationCell);
    getCurrentPlayer().addScore(destPiece.getScoreValue());

    delete currentlySelectedCell;
    currentlySelectedCell = nullptr;
    return true;
}

void Game::advance() {
    move += 1;
    if(move == 2) {
        move = 0;
        turn += 1;
        if(turn == 4) turn = 0;
    }
}

QPoint Game::getCurrentlySelectedCell() const {
    return *currentlySelectedCell;
}

const QPair<int, int> &Game::getDice() const {
    return dice;
}

int Game::getMove() const {
    return move;
}

int Game::getTurn() const {
    return turn;
}

Player& Game::getCurrentPlayer(){
    return players[turn];
}