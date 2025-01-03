//
// Created by ebbew on 3-1-2025.
//

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
};

#endif //CHATURAJI_CLASSIFIEDMOVE_H
