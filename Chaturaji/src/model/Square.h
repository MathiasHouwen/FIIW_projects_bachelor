//
// Created by robin on 8/11/2024.
//

#ifndef SQUARE_H
#define SQUARE_H
#include "Piece.h"


class Square {
private:
    int x;
    int y;
    Piece* piece;
public:
    Square(int x, int y, Piece *piece);
    ~Square();
    Piece* getPiece() const;
    void setPiece(Piece *piece);
    int getX() const;
    int getY() const;
};



#endif //SQUARE_H
