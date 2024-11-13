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
        case 2:
            result.push_back(Type::BOAT);
        case 3:
            result.push_back(Type::KNIGHT);
        case 4:
            result.push_back(Type::ELEPH);
        case 5:
            result.push_back(Type::KING);
            result.push_back(Type::PAWN);
        case 6:
            result.push_back(Type::ELEPH);
    }
    return result;
}

QString Piece::getTypeName(std::vector<Type> type) {
    switch(type[0]) {
        case Type::PAWN: return "Pawn or King";
        case Type::KNIGHT: return "Horse";
        case Type::KING: return "Pawn or King";
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

QString Piece::getShortName() {
    switch(type) {
        case Piece::Type::PAWN: return "pawn";
        case Piece::Type::KNIGHT: return "horse";
        case Piece::Type::KING: return "king";
        case Piece::Type::BOAT: return "boat";
        case Piece::Type::ELEPH: return "eleph";
        default: return "invalid";
    }
}

QString Piece::getColorName() {
    return Player::getColourName(player.getColour());
}
