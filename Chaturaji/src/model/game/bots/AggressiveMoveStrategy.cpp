//
// Created by robin on 3/01/2025.
//

#include "AggressiveMoveStrategy.h"

QPoint AggressiveMoveStrategy::getNextMove(Game& game, const QSet<ClassifiedMove>& moves) {
    ClassifiedMove slection = *moves.begin(); // "random" (eerste move)
    // vervang als er een attack move is
    for(auto move : moves){
        if(move.moveType == MoveType::ATTACK)
            slection = move;
    }
    return slection.destination;
}

QPoint AggressiveMoveStrategy::getNextSelectedCell(Game &game, const QSet<QPoint> &selectables) {
    QHash<PieceType, QPoint> pieceTypes;
    for(auto cell : selectables){
        auto type = game.getGameState().getBoard().getPieceAt(cell)->getType();
        pieceTypes[type] = cell;
    }
    // pak pieces die ver bewegen
    if(pieceTypes.contains(PieceType::ELEPHANT)) return pieceTypes[PieceType::ELEPHANT];
    if(pieceTypes.contains(PieceType::BOAT)) return pieceTypes[PieceType::BOAT];
    // anders pak "random" (eerste die je kan vinden)
    for(auto cell : pieceTypes) return cell;
}

