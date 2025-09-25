//practicum 3:
// - Ebbe: gemaakt
// doel: zie model/logic/passive/MovesManager class

#ifndef CHATURAJI_CLASSIFIEDMOVE_H
#define CHATURAJI_CLASSIFIEDMOVE_H

#include <QPoint>

enum class MoveType{
    NORMAL, ATTACK
};

enum class SpecialMoveType{
    NONE, PAWNPROMOTE, VRIHANNAUKA, SINHASANA
};

struct ClassifiedMove{
    QPoint destination;
    MoveType moveType{MoveType::NORMAL};
    SpecialMoveType specialMoveType{SpecialMoveType::NONE};

    bool operator==(const ClassifiedMove &rhs) const {return destination == rhs.destination;}
    bool operator!=(const ClassifiedMove &rhs) const {return !(rhs == *this);}
};

inline uint qHash(const ClassifiedMove &move, uint seed = 0) {
    return qHash(move.destination, seed); // een set mag niet meerdere moves met dezelfde locatie bevatten. Dus locatie is genoeg
}

#endif //CHATURAJI_CLASSIFIEDMOVE_H
