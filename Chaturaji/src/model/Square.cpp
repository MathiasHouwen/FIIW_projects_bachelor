//
// Created by robin on 8/11/2024.
//

#include "Square.h"

Square::Square(int x, int y, Piece *piece)
        : x(x),
          y(y),
          piece(piece) {
}

Square::~Square() {}


Piece *Square::getPiece() const {
    return piece;
}

void Square::setPiece(Piece *piece) {
    this->piece = piece;
}

int Square::getX() const {
    return x;
}

int Square::getY() const {
    return y;
}
