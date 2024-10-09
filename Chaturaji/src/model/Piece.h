//
// Created by ebbew on 9-10-2024.
//

#ifndef CHATURAJI_PIECE_H
#define CHATURAJI_PIECE_H


#include "PatternMover.h"

class Piece {
public:
    enum class Type {PAWN, BOAT, ELEPH, KNIGHT, KING};
    explicit Piece(Type type);

    const PatternMover::Pattern &getWalkPattern() const;

    const PatternMover::Pattern &getAttackPattern() const;

private:
    PatternMover::Pattern walkPattern;
    PatternMover::Pattern attackPattern;
    Type type;
public:
    Type getType() const;
};


#endif //CHATURAJI_PIECE_H
