//
// Created by ebbew on 9-10-2024.
//

#include "Piece.h"


Piece::Type Piece::getType() const {
    return type;
}

Piece::Piece(Piece::Type type) : type(type) {
    switch (type) {
        case Type::BOAT:
            walkPattern = {2, {2}, false, false};
            attackPattern = walkPattern;
            break;
        case Type::ELEPH:
            walkPattern = {1, {0}, false, true};
            attackPattern = walkPattern;
            break;
        case Type::KNIGHT:
            walkPattern = {2, {-1,1}, false, false};
            attackPattern = walkPattern;
            break;
        case Type::KING:
            walkPattern = {1, {0,1}, false, false};
            attackPattern = walkPattern;
            break;
        case Type::PAWN:
            walkPattern = {1, {0}, true, false};
            attackPattern = {1, {-1,1}, true, false};
            break;
    }
}

const PatternMover::Pattern &Piece::getWalkPattern() const {
    return walkPattern;
}

const PatternMover::Pattern &Piece::getAttackPattern() const {
    return attackPattern;
}
