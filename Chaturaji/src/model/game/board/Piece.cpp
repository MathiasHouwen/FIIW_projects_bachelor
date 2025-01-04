//
// Created by ebbew on 2-1-2025.
//

#include "Piece.h"

Color Piece::getColor() const {
    return color;
}

Piece::Piece(Color color, PieceType type)
    : color(color), type(type)
{}

PieceType Piece::getType() const {
    return type;
}

HomeBoardSide Piece::getHomeSide() const {
    return homeSide;
}

