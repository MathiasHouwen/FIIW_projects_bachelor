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
    if(fromRow + toRow <= width * 2
    && fromCol + toCol <= height * 2
    && toCol >= 0
    && toRow >= 0) {
         setCell(fromRow, fromCol, false);
         setCell(toRow, toCol, true);
    }
    else{cout << "invalid cell at " << toRow << ", " << toCol << endl;}
}


