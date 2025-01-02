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

QList<Piece> BoardQuerier::getPiecesFromColor(Color color) {
    // Log N is niet erg want board is toch maar klein
    QList<Piece> result{};
    for(auto piece : board){
        if(piece.getColor() == color) result.append(piece);
    }
    return result;
}
