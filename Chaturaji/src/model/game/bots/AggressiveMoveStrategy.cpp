//
// Created by robin on 3/01/2025.
//

#include "AggressiveMoveStrategy.h"

QPoint AggressiveMoveStrategy::getNextMove(Game& game, const QSet<QPoint>& moves) {
    Piece calculated{Piece::Type::KING, {0, 0}, game.getCurrentPlayer(), {NULL, NULL}};
    for (const auto& move : moves) {
        Piece* destPiece = game.getBoard().getCell(move);
        if (destPiece) return destPiece->getCell();
        Piece dummy{Piece::Type::KING, {0, 0}, game.getCurrentPlayer(), move};
        if (dummy > calculated) calculated.setCell(move);
    }
    return calculated.getCell();
}