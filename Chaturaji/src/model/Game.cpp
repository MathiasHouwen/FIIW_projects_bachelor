

#include <iostream>
#include <ctime>
#include "Game.h"
#include "Piece.h"

Game::Game() : board(), mover(board) {
    currentlySelectedCell = nullptr;
}

Board& Game::getBoard() {
    return board;
}

void Game::doubleDobbel() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    dice.first = piece.getTypeFromDobbel(std::rand() % 6 + 1);
    dice.second = piece.getTypeFromDobbel(std::rand() % 6 + 1);
}

void Game::namePlayer(const QString& name, int playerIndex) {
    Player& player = players[playerIndex];
    player.setMName(name);
}

bool Game::selectPiece(QPoint cell) {
    if(board.isCellEmpty(cell)) return false;
    Piece piece = *board.getCell(cell);
    if(piece.getPlayer() != getCurrentPlayer()) return false;

    if(piece.getType() == dice.first){
        dice.first = Piece::Type::USED;
    } else if (piece.getType() == dice.second){
        dice.second = Piece::Type::USED;
    } else return false;

    delete currentlySelectedCell;
    currentlySelectedCell = new QPoint(cell);

    return true;
}

bool Game::movePiece(QPoint destinationCell) {
    QSet<QPoint> moves = getPossibleMoves();
    if(!moves.contains(destinationCell)) return false;

    int scoreToAdd = 0;
    Piece* destPiece = board.getCell(destinationCell);
    if(destPiece){
        scoreToAdd = destPiece->getScoreValue();
    }
    board.move(*currentlySelectedCell, destinationCell);
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

QPoint* Game::getCurrentlySelectedCell() const {
    return currentlySelectedCell;
}

const QPair<Piece::Type, Piece::Type> &Game::getDice() const {
    return dice;
}

int Game::getMove() const {
    return move;
}

Player& Game::getCurrentPlayer(){
    return players[turn];
}

Player& Game::getPlayerFromColour(Player::colour colour){
    return players[(int) colour];
}

bool Game::isGameOver() const {
    return gameOver;
}

QSet<QPoint> Game::getPossibleMoves() {
    if(!currentlySelectedCell) return {};
    QPoint cell = *currentlySelectedCell;
    Piece* piece = board.getCell(cell);
    if(!piece) return {};

    QSet<QPoint> walkMoves = mover.getPossibleMoves(piece->getWalkPattern(), cell);
    QSet<QPoint> attackMoves = mover.getPossibleMoves(piece->getWalkPattern(), cell);
    QSet<QPoint> possibleMoves = {};

    for(QPoint move : walkMoves) {
        if(board.isCellEmpty(move))
            possibleMoves.insert(move);
    }

    for(QPoint move : attackMoves){
        if(!board.isCellEmpty(move)){
            Piece targetPiece = *board.getCell(move);
            if(targetPiece.getPlayer() != getCurrentPlayer())
                possibleMoves.insert(move);
        }
    }
    return possibleMoves;
}


