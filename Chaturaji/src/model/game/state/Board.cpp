#include "Board.h"

// volledig door robin (kleine refactors door ebbe)
// practicum 2: enkel logica toegevoegd om piece in board te syncen met piece in player door ebbe


std::optional<Piece> Board::getPieceAt(const QPoint& cell) const {
    if(errorIfOutOfRane(cell)) return std::nullopt;
    return piecesMap[cell];
}

void Board::putPieceAt(const QPoint& cell, Piece piece) {
    if(errorIfOutOfRane(cell)) return;
    piecesMap[cell] = piece;
}

void Board::clearCell(const QPoint& cell) {
    if(errorIfOutOfRane(cell)) return;
    piecesMap.remove(cell);
}

void Board::clear() {
    piecesMap.clear();
}

bool Board::isEmptyAt(const QPoint& cell) const {
    if(errorIfOutOfRane(cell)) return false;
    piecesMap.contains(cell);
}

bool Board::errorIfOutOfRane(const QPoint& cell) {
    if(!dimension.includes(cell)){
        qWarning() << "Cell [" << cell.x() << ", " << cell.y() << "] out of range";
        return true;
    }
    return false;
}
