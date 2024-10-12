//
// Created by ebbew on 9-10-2024.
//

#include "Piece.h"

#include <utility>


Piece::Type Piece::getType() const {
    return type;
}
int Piece::getScoreValue() const {
    return scoreValue;
}
Player &Piece::getPlayer() const {
    return player;
}

Piece::Piece(Piece::Type type, QPoint direction, Player& player) : type(type), player(player){
    switch (type) {
        case Type::BOAT:
            init({2, {2}, false, false, direction}, 2);
            break;
        case Type::ELEPH:
            init({1, {0}, false, true, direction}, 4);
            break;
        case Type::KNIGHT:
            init({2, {-1,1}, false, false, direction}, 3);
            break;
        case Type::KING:
            init({1, {0,1}, false, false, direction}, 5);
            break;
        case Type::PAWN:
            init({1, {0}, true, false, direction}, 1);
            attackPattern = {1, {-1,1}, true, false, direction};
            break;
    }
}

const Pattern &Piece::getWalkPattern() const {
    return walkPattern;
}

const Pattern &Piece::getAttackPattern() const {
    return attackPattern;
}

void Piece::init(Pattern pattern, int scoreValue) {
    walkPattern = std::move(pattern);
    attackPattern = walkPattern;
    this->scoreValue = scoreValue;
}
