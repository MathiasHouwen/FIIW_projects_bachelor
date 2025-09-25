// taakverdeling: zie h-file


#include "Piece.h"

Color Piece::getColor() const {
    return color;
}

Piece::Piece(Color color, PieceType type, HomeBoardSide homeSide)
    : color(color), type(type), homeSide(homeSide)
{}

PieceType Piece::getType() const {
    return type;
}

HomeBoardSide Piece::getHomeSide() const {
    return homeSide;
}

