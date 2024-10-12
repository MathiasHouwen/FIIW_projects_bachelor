

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

void Game::namePlayer(const QString& name, int playerIndex) {
    Player& player = players[playerIndex];
    player.setMName(name);
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

    QPoint fromCell = *currentlySelectedCell;
    Piece sourcePiece = *board.getCell(fromCell);

    Pattern pattern;
    int scoreToAdd = 0;
    if(empty){
        pattern = sourcePiece.getWalkPattern();
    } else {
        Piece destPiece = *board.getCell(destinationCell);
        if(destPiece.player == getCurrentPlayer()) return false;
        pattern = sourcePiece.getAttackPattern();
        scoreToAdd = destPiece.getScoreValue();
    }

    QSet<QPoint> moves = mover.getPossibleMoves(pattern, fromCell);
    if(!moves.contains(destinationCell)) return false;

    board.move(fromCell, destinationCell);
    getCurrentPlayer().addScore(scoreToAdd);

    delete currentlySelectedCell;
    currentlySelectedCell = nullptr;
    return true;
}

void Game::advance() {
    move++;
    if(move > 1) {
        move = 0;
        int turnAttempts;
        for(turnAttempts=1; turnAttempts<=4; turnAttempts++){
            turn++;
            if(turn == 4) turn = 0;
            if(getCurrentPlayer().isAlive()) break;
        }
        gameOver = turnAttempts >= 4;
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

bool Game::isGameOver() const {
    return gameOver;
}
