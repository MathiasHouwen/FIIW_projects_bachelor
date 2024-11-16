

#include <iostream>
#include <ctime>
#include "Game.h"
#include "Piece.h"
// select, move, advance en getpossiblemoves door ebbe
// dobbel generatie door mathias
// dobbel validatie en implementatie in select door robin

Game::Game() : board(), mover(board) {
    currentlySelectedCell = nullptr;
    emit somethingChanged();
}

void Game::setPlayerName(const QString& name, Player::colour playerColour) {
    players[static_cast<int>(playerColour)].setName(name);
}
void Game::setPlayerScore(int score, Player::colour playerColour){
    Player player = getPlayerFromColour(playerColour);
    player.setMScore(score);
}

bool Game::selectPiece(QPoint cell) {
    if(board.isCellEmpty(cell)) return false;   // mag geen leeg vak selecteren
    Piece piece = *board.getCell(cell);
    if(piece.getPlayer() != getCurrentPlayer()) return false;   // mag enkel jouw eigen piece selecteren
    if(!dice.allows(piece.getType())) return false;
    // update selectie
    delete currentlySelectedCell;
    currentlySelectedCell = new QPoint(cell);
    moveState = MoveState::READYTOMOVE;
    return true;
}

bool Game::movePiece(QPoint destinationCell) {
    QSet<QPoint> moves = getPossibleMoves(); // get mogelijke moves voor selectie
    if(destinationCell == *currentlySelectedCell){
        moveState = MoveState::READYTOSELECT;
        return true;
    }
    if(!moves.contains(destinationCell)) return false;  // keuze van eind-cell moet in mogelijke moves zitten

    Piece piece = *board.getCell(*currentlySelectedCell);
    dice.setUsed(piece.getType());

    Piece* destPiece = board.getCell(destinationCell);
    int scoreToAdd = destPiece ? destPiece->getScoreValue() : 0;

    if (destPiece && destPiece->getType() == Piece::Type::KING) {
        destPiece->getPlayer().killPlayer();
    }

    // doe de move in bord en update score
    board.move(*currentlySelectedCell, destinationCell);
    getCurrentPlayer().addScore(scoreToAdd);

    // maak selectie leeg
    delete currentlySelectedCell;
    currentlySelectedCell = nullptr;
    moveState = MoveState::READYTOSELECT;
    advance();
    return true;
}

void Game::advance() {
    move++;
    if(move > 1) { // als 2e move voorbij, reset move en advance de turn
        dice.doubleDobbel();
        move = 0;
        // probeer 4 keer de turn te verzetten
        int turnAttempts;
        for(turnAttempts=1; turnAttempts<=4; turnAttempts++){
            emit nextTurn();
            turn++;
            if(turn == 4) turn = 0;
            if(getCurrentPlayer().isAlive()) break; // probeer opnieuw als de speler dood is
        }
        // als 4 keer geprobeerd dan was iedereen dood, dus game over
        gameOver = turnAttempts >= 4;
    }
    emit somethingChanged();

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
Player& Game::getCurrentPlayer(){
    return players[turn];
}
Player& Game::getPlayerFromColour(Player::colour colour){
    return players[(int) colour];
}

QPoint* Game::getCurrentlySelectedCell() const {return currentlySelectedCell;}
int Game::getMove() const {return move;}
Board& Game::getBoard() {return board;}
bool Game::isGameOver() const {return gameOver;}
const Player *Game::getPlayers() const {return players;}
Game::MoveState Game::getMoveState() const{return moveState;}

QSet<QPoint> Game::getPossibleSelections() {
    QSet<QPoint> selectables{};
    for(int x=0; x<Board::getSize(); x++){
    for(int y=0; y<Board::getSize(); y++){
        Piece* piece = board.getCell({x,y});
        if(!piece) continue;
        if(piece->getPlayer() == getCurrentPlayer() && dice.allows(piece->getType()))
            selectables.insert({x,y});
    }}
    return selectables;
}

void Game::skip() {
    advance();
}

Dice Game::getDice() {
    return dice;
}

const int Game::getNumberOfPlayer() {
    return numberOfPlayer;
}


