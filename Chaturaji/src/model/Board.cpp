#include "Board.h"
#include <iostream>

using namespace std;

Piece* Board::getCell(const QPoint cell) const {
    errorIfOutOfRane(cell);
    return board[cell.y()][cell.x()];
}

void Board::setCell(const QPoint cell, Piece piece) {
    errorIfOutOfRane(cell);
    Piece* p = new Piece(piece.getType(), piece.direction, piece.player);
    board[cell.y()][cell.x()] = p;
}

void Board::removecell(QPoint cell) {
    errorIfOutOfRane(cell);
    delete board[cell.y()][cell.x()];
    board[cell.y()][cell.x()] = nullptr; //TODO mag deze weg?
}

void Board::move(QPoint fromCell, QPoint toCell) {
    Piece* from = getCell(fromCell);
    removecell(fromCell);
    setCell(toCell, *from);
}

void Board::setAllNull() {
    for (auto & i : board) {
        for (Piece* & j : i) {
            j = nullptr;
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



