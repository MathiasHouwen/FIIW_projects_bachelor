//
// Created by ebbew on 5-1-2025.
//

#include "Game.h"

bool Game::doMove(QPoint from, QPoint to, PieceType pawnPromoteType) {
    if(gameState.getBoard().isEmptyAt(from)) return false;
    auto fromPiece = gameState.getBoard().getPieceAt(from);
    auto moves = movesManager.generateClassifiedMoves(fromPiece.value(), from);
    for(auto move : moves){
        if(move.destination == to){
            executeClassifiedMove(from, move, pawnPromoteType);
            return true;
        }
    }
    return false;
}

Game::Game()
    : movesManager(gameState.getBoard()),
    querier(gameState.getBoard()),
    rulesExecutor(gameState.getBoard())
    {}

void Game::executeClassifiedMove(QPoint from, ClassifiedMove move, PieceType pawnPromoteType) {
    auto killedPiece = querier.movePiece(from, move.destination);
    if(move.moveType == MoveType::ATTACK){
        int score = pieceTypeToScore(killedPiece.value().getType());
        gameState.getCurrentPlayer().increaseScore(score);
    }
    switch (move.specialMoveType) {
        case SpecialMoveType::SINHASANA:
            rulesExecutor.sinhasana(move.destination);
            break;
        case SpecialMoveType::VRIHANNAUKA:
            rulesExecutor.vrihannauka(move.destination);
            break;
        case SpecialMoveType::PAWNPROMOTE:
            rulesExecutor.promotePawn(move.destination, pawnPromoteType);
            break;
        case SpecialMoveType::NONE:
            break;
    }
}

int Game::pieceTypeToScore(PieceType type) {
    switch (type) {
        case PieceType::PAWN: return 1;
        case PieceType::BOAT: return 2;
        case PieceType::HORSE: return 3;
        case PieceType::ELEPHANT: return 4;
        case PieceType::KING: return 5;
    }
}
