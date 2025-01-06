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
    int topLeftX, topLeftY;
    // zoek de topleft corner (de special rules checker class heeft al gevalidate dat er 4 boten bestan)
    QPoint leftX = {location.x()-1, location.y()};
    QPoint topY = {location.x(), location.y()-1};
    if(Board::dimension.includes(leftX) && !board.isEmptyAt(leftX)){
        topLeftX = board.getPieceAt(leftX).value().getType() == PieceType::BOAT
                ? leftX.x() : location.x();
    }
    if(Board::dimension.includes(topY) && !board.isEmptyAt(topY)){
        topLeftY = board.getPieceAt(topY).value().getType() == PieceType::BOAT
                   ? topY.y() : location.y();
    }
    captureBoats({topLeftX, topLeftY}, board.getPieceAt(location)->getColor());
}

void SpecialRulesExecutor::sinhasana(QPoint location) {
    auto currentPiece = board.getPieceAt(location);
    HomeBoardSide sides[4] = {HomeBoardSide::LEFT, HomeBoardSide::RIGHT, HomeBoardSide::TOP, HomeBoardSide::BOTTOM};
    // vind de side
    HomeBoardSide capturedSide;
    for(auto side : sides){
        if(querier.isPointFromBoardSideEdge(location, side))
            capturedSide = side;
    }
    // vind alle pieces van die side
    auto cells = querier.getPiecesFromBoardHomeSide(capturedSide);
    // maak al die pieces van jou
    for(auto cell : cells){
        auto piece = board.getPieceAt(cell);
        Piece newPiece(currentPiece->getColor(), piece->getType(), piece->getHomeSide());
        board.putPieceAt(cell, newPiece);
    }
}

void SpecialRulesExecutor::captureBoats(QPoint topLeft, Color ownColor) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            QPoint cell(topLeft.x() + i, topLeft.y() + j);
            if(board.getPieceAt(cell)->getColor() == ownColor) continue;
            board.clearCell(cell);
        }
    }
}