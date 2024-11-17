#include "Board.h"
#include <iostream>
#include <utility>

// volledig door robin (kleine refactors door ebbe)

Piece* Board::getCell(const QPoint cell) const {
    errorIfOutOfRane(cell); // randgeval
    return board[cell.y()][cell.x()];
}

void Board::setCell(const QPoint cell, Piece piece) {
    Piece* oldPiece = getCell(cell);
    if(oldPiece){
        oldPiece->getPlayer().removePiece(oldPiece);
    }
    delete oldPiece;    // delete oude piece eerst van heap
    auto newPiece = new Piece(std::move(piece));    // maakt kopie van niewe piece op de heap
    newPiece->setCell(cell);
    newPiece->getPlayer().addPiece(newPiece);
    board[cell.y()][cell.x()] = newPiece;
}

void Board::move(QPoint fromCell, QPoint toCell) {
    Piece* from = getCell(fromCell);    // get oude piece
    from->setCell(toCell);
    board[fromCell.y()][fromCell.x()] = nullptr; // oude cell op null
    setCell(toCell, *from);  // nieuwe cell wordt oude piece
}

void Board::clear() {
    for (auto & i : board) {
        for (Piece* & j : i) {
            delete j;
            j = nullptr; //kan omdat j een reference is
        }
    }
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



