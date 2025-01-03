//
// Created by ebbew on 2-1-2025.
//

#ifndef CHATURAJI_PIECE_H
#define CHATURAJI_PIECE_H


#include "../../enums_and_structs/Color.h"
#include "../../enums_and_structs/PieceType.h"

class Piece {
private:
    Color color{Color::NONE};
    PieceType type{PieceType::PAWN};
public:
    Piece() = default; // nodig voor maps
    explicit Piece(Color color, PieceType type);
    Color getColor();
};


#endif //CHATURAJI_PIECE_H
