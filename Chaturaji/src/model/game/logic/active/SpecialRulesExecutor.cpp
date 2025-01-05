//
// Created by ebbew on 5-1-2025.
//

#include "SpecialRulesExecutor.h"

SpecialRulesExecutor::SpecialRulesExecutor(Board &board) : board(board), querier{board} {}

void SpecialRulesExecutor::promotePawn(QPoint location, PieceType newPieceType) {
    auto currentPiece = board.getPieceAt(location);
    Piece newPiece(currentPiece->getColor(), newPieceType, currentPiece->getHomeSide());
    board.putPieceAt(location, newPiece);
}
