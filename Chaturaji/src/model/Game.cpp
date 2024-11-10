

#include <iostream>
#include <ctime>
#include "Game.h"
#include "Piece.h"
// select, move, advance en getpossiblemoves door ebbe
// dobbel generatie door mathias
// dobbel validatie en implementatie in select door robin

Game::Game() : board(), mover(board) {
    currentlySelectedCell = nullptr;
}

void Game::doubleDobbel() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    dice.first = Piece::getTypeFromDobbel(std::rand() % 6 + 1);
    dice.second = Piece::getTypeFromDobbel(std::rand() % 6 + 1);
    emit somethingChanged();
}

void Game::namePlayer(const QString& name, int playerIndex) {
    Player& player = players[playerIndex];
    player.setName(name);
}

bool Game::selectPiece(QPoint cell) {
    if(board.isCellEmpty(cell)) return false;   // mag geen leeg vak selecteren
    Piece piece = *board.getCell(cell);
    if(piece.getPlayer() != getCurrentPlayer()) return false;   // mag enkel jouw eigen piece selecteren

    if(piece.getType() == dice.first){  // mag enkel een piece selecteren met type van de gegooide dobbelsteen
        dice.first = Piece::Type::USED; // used = bobbelsteen is al gekozen in vorige move
        emit somethingChanged();
    } else if (piece.getType() == dice.second){
        dice.second = Piece::Type::USED;
        emit somethingChanged();
    } else return false;

    // update selectie
    delete currentlySelectedCell;
    currentlySelectedCell = new QPoint(cell);

    return true;
}

bool Game::movePiece(QPoint destinationCell) {
    QSet<QPoint> moves = getPossibleMoves(); // get mogelijke moves voor selectie
    if(!moves.contains(destinationCell)) return false;  // keuze van eind-cell moet in mogelijke moves zitten

    int scoreToAdd = 0;
    Piece* destPiece = board.getCell(destinationCell);
    // als er een piece ligt, is dit een aanval, dus worden punten geteld
    // kijken of aanval mag, of als je gewoon naar een leeg vakje loop is gedaan in getPossibleMoves
    if(destPiece){
        scoreToAdd = destPiece->getScoreValue();
    }
    // doe de move in bord en update score
    board.move(*currentlySelectedCell, destinationCell);
    getCurrentPlayer().addScore(scoreToAdd);

    // maak selectie leeg
    delete currentlySelectedCell;
    currentlySelectedCell = nullptr;
    return true;
}

void Game::advance() {
    move++;
    if(move > 1) { // als 2e move voorbij, reset move en advance de turn
        move = 0;
        // probeer 4 keer de turn te verzetten
        int turnAttempts;
        for(turnAttempts=1; turnAttempts<=4; turnAttempts++){
            turn++;
            if(turn == 4) turn = 0;
            if(getCurrentPlayer().isAlive()) break; // probeer opnieuw als de speler dood is
        }
        // als 4 keer geprobeerd dan was iedereen dood, dus game over
        gameOver = turnAttempts >= 4;
    }
}

QSet<QPoint> Game::getPossibleMoves() {
    if(!currentlySelectedCell) return {};   // als er geen selectie is gedaan zijn er geen moves
    QPoint cell = *currentlySelectedCell;
    Piece* piece = board.getCell(cell);
    if(!piece) return {};   // als de selectie een lege cell is zijn er geen moves

    // haal de loop en aanval pattronen
    QSet<QPoint> walkMoves = mover.getPossibleMoves(piece->getWalkPattern(), cell);
    QSet<QPoint> attackMoves = mover.getPossibleMoves(piece->getAttackPattern(), cell);
    QSet<QPoint> possibleMoves = {};

    for(QPoint move : walkMoves) {
        if(board.isCellEmpty(move)) // lopen mag alleen naar een lege cell
            possibleMoves.insert(move);
    }

    for(QPoint move : attackMoves){
        if(!board.isCellEmpty(move)){ // aanvallen mag alleen op een andere piece
            Piece targetPiece = *board.getCell(move);
            if(targetPiece.getPlayer() != getCurrentPlayer())  // die andere piece mag niet van jou zelf zijn
                possibleMoves.insert(move);
        }
    }
    return possibleMoves;
}


/*
 * SIMPELE GETTERS
 */

QPoint* Game::getCurrentlySelectedCell() const {
    return currentlySelectedCell;
}
const QPair<Piece::Type, Piece::Type> &Game::getDice() const {
    return dice;
}
int Game::getMove() const {
    return move;
}
Board& Game::getBoard() {
    return board;
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


