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

void SpecialRulesExecutor::vrihannauka(QPoint location) {
    std::vector<QPoint> topLeftCorners = {
            QPoint(location.x() - 1, location.y() - 1),
            QPoint(location.x(), location.y() - 1),
            QPoint(location.x() - 1, location.y()),
            QPoint(location.x(), location.y())
    };
    for (const auto& corner : topLeftCorners) {
        if (isSquareFilledWithBoats(corner)) {
            captureBoats(corner);
            return;
        }
    }
}

void SpecialRulesExecutor::sinhasana(QPoint location) {
    auto currentPiece = board.getPieceAt(location);
    HomeBoardSide side;
    if(location.x() == 0){
        side = HomeBoardSide::LEFT;
    } else if(location.x() == 8){
        side = HomeBoardSide::RIGHT;
    } else if(location.y() == 0){
        side = HomeBoardSide::TOP;
    } else{
        side = HomeBoardSide::BOTTOM;
    }
    // vind alle pieces van die side
    auto cells = querier.getPiecesFromBoardHomeSide(side);
    // maak al die pieces van jou
    for(auto cell : cells){
        auto piece = board.getPieceAt(cell);
        Piece newPiece(currentPiece->getColor(), piece->getType(), piece->getHomeSide());
        board.putPieceAt(location, newPiece);
    }
}

void SpecialRulesExecutor::captureBoats(QPoint topLeft) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            QPoint cell(topLeft.x() + i, topLeft.y() + j);
            board.clearCell(cell);
        }
    }
}

bool SpecialRulesExecutor::isSquareFilledWithBoats(QPoint topLeft) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            QPoint cell(topLeft.x() + i, topLeft.y() + j);
            if (!Board::dimension.includes(cell) || board.isEmptyAt(cell) || board.getPieceAt(cell)->getType() != PieceType::BOAT) {
                return false;
            }
        }
    }
    return true;
}