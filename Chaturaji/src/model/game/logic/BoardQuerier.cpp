//
// Created by ebbew on 2-1-2025.
//

#include "BoardQuerier.h"

std::optional<Piece> BoardQuerier::movePiece(QPoint fromCell, QPoint toCell) {
    if(board.isEmptyAt(fromCell)){
        qWarning() << "no piece to move at " << fromCell;
        return std::nullopt;
    }
    auto fromPiece = board.getPieceAt(fromCell);
    auto toPiece = board.getPieceAt(toCell);
    board.putPieceAt(toCell, fromPiece.value()); // frompiece.value() bestaat als isEmptyAt false is
    board.clearCell(fromCell);
    return toPiece;
}

QSet<QPoint> BoardQuerier::getPiecesFromColor(Color color) {
    // Log N is niet erg want board is toch maar klein
    QSet<QPoint> result{};
    for(auto cell : board){
        if(board.getPieceAt(cell)->getColor() == color) result.insert(cell);
    }
    return result;
}

BoardQuerier::BoardQuerier(Board &board) : board(board) {}

QSet<QPoint> BoardQuerier::getPiecesFromBoardHomeSide(HomeBoardSide homeSide) {
    // Log N is niet erg want board is toch maar klein
    QSet<QPoint> result{};
    for(auto cell : board){
        if(board.getPieceAt(cell)->getHomeSide() == homeSide) result.insert(cell);
    }
    return result;
}

QSet<QPoint> BoardQuerier::getPiecesWithTypesAndColor(QSet<PieceType> types, Color color) {
    // Log N is niet erg want board is toch maar klein
    QSet<QPoint> result{};
    QSet<QPoint> colorPieces = getPiecesFromColor(color);
    for(auto cell : colorPieces){
        if(types.contains(board.getPieceAt(cell)->getType())) result.insert(cell);
    }
    return result;
}
