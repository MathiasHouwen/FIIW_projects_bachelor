//
// Created by ebbew on 2-1-2025.
//

#ifndef CHATURAJI_PIECE_H
#define CHATURAJI_PIECE_H


#include "../../enums_and_structs/Color.h"
#include "../../enums_and_structs/PieceType.h"
#include "../../enums_and_structs/HomeBoardSide.h"

class Piece {
private:
    Color color{Color::NONE};
    PieceType type{PieceType::PAWN};
    HomeBoardSide homeSide{HomeBoardSide::LEFT};
public:
    Piece() = default; // nodig voor maps
    explicit Piece(Color color, PieceType type, HomeBoardSide homeSide);

    [[nodiscard]] PieceType getType() const;
    [[nodiscard]] HomeBoardSide getHomeSide() const;
    [[nodiscard]] Color getColor() const;
};


#endif //CHATURAJI_PIECE_H
