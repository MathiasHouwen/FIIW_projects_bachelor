//
// Created by ebbew on 2-1-2025.
//

#ifndef CHATURAJI_PIECE_H
#define CHATURAJI_PIECE_H


#include "../Color.h"

class Piece {
private:
    Color color{Color::NONE};
public:
    Piece(Color color);
    Color getColor();
};


#endif //CHATURAJI_PIECE_H
