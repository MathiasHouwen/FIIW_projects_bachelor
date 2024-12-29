// gemaakt door ebbe en mathias tegenlijk en ge-merged
//practicum 2: enkel cell (+get/set) toegevoegd door ebbe

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

Piece::Piece(Piece::Type type, QPoint direction, Player& player, QPoint cell) : type(type), player(player), cell(cell){
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

const QPoint &Piece::getCell() const {
    return cell;
}
void Piece::setCell(const QPoint &cell) {
    Piece::cell = cell;
}

bool Piece::operator>(const Piece &other) const {
    if(other.cell.x() == NULL || other.cell.y() == NULL){return true;}
    int myX = this->cell.x()*walkPattern.forwardDirection.x();
    int myY = this->cell.y()*walkPattern.forwardDirection.y()*-1;
    int otherX = other.cell.x()*walkPattern.forwardDirection.x();
    int otherY = other.cell.y()*walkPattern.forwardDirection.y()*-1;
    return myX >= otherX && myY >= otherY;
}

bool Piece::operator<(const Piece &other) const {
    if(other.cell.x() == NULL || other.cell.y() == NULL){return true;}
    int myX = this->cell.x()*walkPattern.forwardDirection.x();
    int myY = this->cell.y()*walkPattern.forwardDirection.y()*-1;
    int otherX = other.cell.x()*walkPattern.forwardDirection.x();
    int otherY = other.cell.y()*walkPattern.forwardDirection.y()*-1;
    return myX <= otherX && myY <= otherY;
}
