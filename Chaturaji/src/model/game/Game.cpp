#include <iostream>
#include "Game.h"

#include <qtextstream.h>

#include "board/Piece.h"
// select, move, advance en getpossiblemoves door ebbe
// dobbel generatie door mathias
// dobbel validatie en implementatie in select door robin

Game::Game() : board(), mover(board) {
    currentlySelectedCell = nullptr;
}

void Game::setPlayerName(const QString& name, Player::colour playerColour) {
    players[static_cast<int>(playerColour)]->setName(name);
}

void Game::setPlayerScore(int score, Player::colour playerColour){
    Player player = getPlayerFromColour(playerColour);
    player.setMScore(score);
}

void Game::makeBot(Player::colour color, bool agressive) {
    players[static_cast<int>(color)] = std::make_shared<Bot>(color, agressive);
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

Game::MoveResult Game::movePiece(QPoint destinationCell) {
    MoveResult result;
    QSet<QPoint> moves = getPossibleMoves(); // get mogelijke moves voor selectie
    if(destinationCell == *currentlySelectedCell){
        moveState = MoveState::READYTOSELECT;
        result.succes = true;
        return result;
    }
    if(!moves.contains(destinationCell)) return result;  // keuze van eind-cell moet in mogelijke moves zitten

    Piece piece = *board.getCell(*currentlySelectedCell);
    dice.setUsed(piece.getType());

    Piece* destPiece = board.getCell(destinationCell);
    int scoreToAdd = destPiece ? destPiece->getScoreValue() : 0;
    result.affectedPiece = destPiece;

    if (destPiece && destPiece->getType() == Piece::Type::KING) {
        destPiece->getPlayer().killPlayer();
        result.affectedPlayer = &destPiece->getPlayer();
    }

    // doe de move in bord en update score
    board.move(*currentlySelectedCell, destinationCell);
    getCurrentPlayer().addScore(scoreToAdd);

    // maak selectie leeg
    delete currentlySelectedCell;
    currentlySelectedCell = nullptr;
    moveState = MoveState::READYTOSELECT;
    advance();
    result.succes = true;
    return result;
}

QPoint Game::getNextMove(const QSet<QPoint>& moves) {
    bool aggressive = std::dynamic_pointer_cast<Bot>(players[turn])->getAggressive();
    Piece calculated{Piece::Type::KING, {0, 0}, getCurrentPlayer(), {NULL, NULL}};
    if(aggressive) {
        for(auto move : moves) {
            Piece* destPiece = board.getCell(move);
            if(destPiece) {return destPiece->getCell();}
            Piece dummy{Piece::Type::KING, {0, 0}, getCurrentPlayer(), move};
            if(dummy.operator>(calculated)){calculated.setCell(move);}
        }
    }
    else {
        for(auto move : moves) {
            Piece* destPiece = board.getCell(move);
            if(destPiece) {continue;}
            Piece dummy{Piece::Type::KING, {0, 0}, getCurrentPlayer(), move};
            if(dummy.operator<(calculated)){calculated.setCell(move);}
        }
    }
    return calculated.getCell();
}

QPoint Game::moveBotPiece() {
    moveState = MoveState::BOT;
    QSet<QPoint> moves = getPossibleMoves();
    std::cout << "can move to: ";
    for(auto move : moves) {
        std::cout << move.x() << "," << move.y() << "; ";
    }
    std::cout << std::endl;
    if(moves.isEmpty()) {
        return {NULL, NULL};
    }
    return getNextMove(moves);
}

QPoint Game::playBot() {
    QList<Piece*> availablePieces{};
    moveState = MoveState::READYTOSELECT;
    for(auto piece : getCurrentPlayer().getAlivePieces()) {
        for(auto type : dice.getAllowedTypes()) {
            if(piece->getType() == type) {
                availablePieces.append(piece);
            }
        }
    }
    if(availablePieces.isEmpty()) {return {NULL, NULL};}

    int randomIndex = rand() % availablePieces.size();
    return availablePieces[randomIndex]->getCell();
}

void Game::advance() {
    move++;
    if(move > 1) { // als 2e move voorbij, reset move en advance de turn
        dice.doubleDobbel();
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
        if (std::dynamic_pointer_cast<Bot>(players[turn]) != nullptr) {
            moveState = MoveState::BOT;
        }
        else {moveState = MoveState::READYTOSELECT;}
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
Player& Game::getCurrentPlayer(){
    return *players[turn];
}
Player& Game::getPlayerFromColour(Player::colour colour){
    return *players[(int) colour];
}

QPoint* Game::getCurrentlySelectedCell() const {return currentlySelectedCell;}
int Game::getMove() const {return move;}
Board& Game::getBoard() {return board;}
bool Game::isGameOver() const {return gameOver;}
std::vector<std::shared_ptr<Player>> Game::getPlayers() const {return players;}
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

int Game::getNumberOfPlayer() {
    return numberOfPlayer;
}

bool Game::promote(QPoint *selectedCell){
    Piece piece = *board.getCell(*selectedCell);
    Piece::Type type = piece.getType();

    // TODO: ASK FOR WICH TO PROMOTO AND PROMOTE THEM
}

bool Game::canPromote(QPoint *selectedCell){
    Piece piece = *board.getCell(*selectedCell);
    Piece::Type type = piece.getType();

    if(type != Piece::Type::PAWN){
        return false;
    }

    Player player = piece.getPlayer();
    // TODO: CHECK IF IT IS IN THE TOP SQAURE
}

bool Game::sinhasana(QPoint *selectedCell) {
    Piece piece = *board.getCell(*selectedCell);
    Piece::Type type = piece.getType();

    if(type != Piece::Type::KING){
        return false;
    }

    // TODO: ja idk nog niet hoe ik deze moet krijgen :/
    std::unordered_map<Player*, QPoint> kingPositions;
    for (const auto &position : kingPositions){
        QPoint kingCell = position.second;

        // TODO: CHECK IF PLAYER IS ALLIED???
        if(&kingCell == selectedCell){
            Piece piece = *board.getCell(*selectedCell);
            mergeArmies(position.first, &(piece.getPlayer()));
        }
    }
    return true;
}

void Game::mergeArmies(Player *fromPlayer, Player *toPlayer){

}


bool Game::vrihannauka(QPoint *selectedCell) {
    Piece piece = *board.getCell(*selectedCell);
    Piece::Type type = piece.getType();
    Player player = piece.getPlayer();


    if (type != Piece::Type::BOAT) {
        return false;
    }

    std::vector<QPoint> topLeftCorners = {
            QPoint(selectedCell->x() - 1, selectedCell->y() - 1),
            QPoint(selectedCell->x(), selectedCell->y() - 1),
            QPoint(selectedCell->x() - 1, selectedCell->y()),
            QPoint(selectedCell->x(), selectedCell->y())
    };

    for (const auto& corner : topLeftCorners) {
        if (isSquareFilledWithBoats(corner)) {
            captureBoats(corner, player);
            return true;
        }
    }

    return false;
}

void Game::captureBoats(QPoint topLeft, Player &safe) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            QPoint cell(topLeft.x() + i, topLeft.y() + j);
            Piece* piece = board.getCell(cell);

            if (piece->getPlayer() != safe){
                piece->getPlayer().removePiece(piece);
                board.clearCell(cell);
            }
        }
    }
}

bool Game::isSquareFilledWithBoats(QPoint topLeft) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            QPoint cell(topLeft.x() + i, topLeft.y() + j);
            if (!board.isInRange(cell) || board.isCellEmpty(cell) || board.getCell(cell)->getType() != Piece::Type::BOAT) {
                return false;
            }
        }
    }
    return true;
}