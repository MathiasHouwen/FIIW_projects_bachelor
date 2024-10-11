#include "Board.h"
#include <iostream>

using namespace std;

Piece Board::getCell(const QPoint cell) {
    errorIfOutOfRane(cell);
    return board[cell.y()][cell.x()];
}

void Board::setCell(const QPoint cell, const Piece &value) {
    errorIfOutOfRane(cell);
    board[cell.y()][cell.x()] = value;
}

void Board::move(QPoint fromCell, QPoint toCell) {
    Piece from = getCell(fromCell);
         setCell(fromCell, from); //TODO nullpointer maken
         setCell(toCell, from);
}

void Board::setAllNull() {
    for (auto & i : board) {
        for (Piece & j : i) {
            j = j; //TODO nullptr maken
        }
    }
}

const int Board::getSize() {
    return size;
}

bool Board::isInRange(QPoint cell) {
    bool xInRange = cell.x() >= 0 && cell.x() <size;
    bool yInRange = cell.y() >= 0 && cell.y() <size;
    return xInRange && yInRange;
}

bool Board::isCellEmpty(QPoint cell) {
    return getCell(cell) == 0; //TODO NULLPTR MAKEN
}

void Board::errorIfOutOfRane(QPoint cell) {
    if(!isInRange(cell))
        std::cerr << "Cell [" << cell.x() << ", " << cell.y() << "] out of range" << std::endl;
}



