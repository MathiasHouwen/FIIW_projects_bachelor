// gemaakt door ebbe en mathias tegenlijk en ge-merged

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

std::vector<Piece::Type> Piece::getTypeFromDobbel(int number) {
    std::vector<Piece::Type> result;
    switch(number) {
        case 1:
            result.push_back(Type::KING);
            result.push_back(Type::PAWN);
            break;
        case 2:
            result.push_back(Type::BOAT);
            break;
        case 3:
            result.push_back(Type::KNIGHT);
            break;
        case 4:
            result.push_back(Type::ELEPH);
            break;
        case 5:
            result.push_back(Type::KING);
            result.push_back(Type::PAWN);
            break;
        case 6:
            result.push_back(Type::ELEPH);
            break;
    }
    return result;
}

QString Piece::getTypeName(Type type) {
    switch(type) {
        case Type::PAWN: return "Pawn";
        case Type::KNIGHT: return "Horse";
        case Type::KING: return "King";
        case Type::BOAT: return "Boat";
        case Type::ELEPH: return "Elephant";
        default: return "invalid";
    }
}

Piece::Type Piece::getTypeFromName(const QString& typestr){
    if (typestr == "Pawn") return Piece::Type::PAWN;
    if (typestr == "Horse") return Piece::Type::KNIGHT;
    if (typestr == "King") return Piece::Type::KING;
    if (typestr == "Elephant") return Piece::Type::ELEPH;
    if (typestr == "Boat") return Piece::Type::BOAT;
    return Piece::Type::USED;
}

QString Piece::getColorName() {
    return Player::getColourName(player.getColour());
}

QString Piece::getTypeName() {
    return getTypeName(type);
}
