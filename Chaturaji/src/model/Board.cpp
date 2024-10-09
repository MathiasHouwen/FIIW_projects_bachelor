#include "Board.h"
#include <iostream>

using namespace std;

bool Board::getCell(QPoint cell) {
    errorIfOutOfRane(cell);
    return board[cell.y()][cell.x()];
}

void Board::setCell(QPoint cell, bool value) {
    errorIfOutOfRane(cell);
    board[cell.y()][cell.x()] = value;
}

void Board::move(QPoint fromCell, QPoint toCell) {
         setCell(fromCell, false);
         setCell(toCell, true);
}

void Board::setAllTrue() {
    for (auto & i : board) {
        for (bool & j : i) {
            j = true;
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
    return getCell(cell) == 0;
}

void Board::errorIfOutOfRane(QPoint cell) {
    if(!isInRange(cell))
        std::cerr << "Cell [" << cell.x() << ", " << cell.y() << "] out of range" << std::endl;
}



