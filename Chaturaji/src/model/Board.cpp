#include "Board.h"
#include <iostream>
#include <utility>

Piece* Board::getCell(const QPoint cell) const {
    errorIfOutOfRane(cell);
    return board[cell.y()][cell.x()];
}

void Board::setCell(const QPoint cell, Piece piece) {
    Piece* oldPiece = getCell(cell);
    delete oldPiece;
    auto newPiece = new Piece(std::move(piece));
    board[cell.y()][cell.x()] = newPiece;
}

void Board::move(QPoint fromCell, QPoint toCell) {
    Piece* from = getCell(fromCell);
    board[fromCell.y()][fromCell.x()] = nullptr;
    setCell(toCell, *from);
}

void Board::clear() {
    for (auto & i : board) {
        for (Piece* & j : i) {
            delete j;
            j = nullptr; //kan omdat j een reference is
        }
    }
}

int Board::getSize() {
    return size;
}

bool Board::isInRange(QPoint cell) {
    bool xInRange = cell.x() >= 0 && cell.x() <size;
    bool yInRange = cell.y() >= 0 && cell.y() <size;
    return xInRange && yInRange;
}

bool Board::isCellEmpty(QPoint cell) const {
    return getCell(cell) == nullptr;
}

void Board::errorIfOutOfRane(QPoint cell) {
    if(!isInRange(cell))
        std::cerr << "Cell [" << cell.x() << ", " << cell.y() << "] out of range" << std::endl;
}



