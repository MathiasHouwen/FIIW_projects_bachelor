#include "Board.h"
#include <stdio.h>
#include <iostream>

using namespace std;

bool Board::getCell(int row, int col) {
    return board[row][col];
}

void Board::setCell(int row, int col, bool value) {
    board[row][col] = value;
}

void Board::move(int toRow, int toCol, int fromRow, int fromCol) {
    if(fromRow + toRow <= size * 2
    && fromCol + toCol <= size * 2
    && toCol >= 0
    && toRow >= 0) {
         setCell(fromRow, fromCol, false);
         setCell(toRow, toCol, true);
    }
    else{cout << "invalid cell at " << toRow << ", " << toCol << endl;}
}

void Board::setAllTrue() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            board[i][j] = true;
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
    return getCell(cell.x(), cell.y()) == 0;
}



