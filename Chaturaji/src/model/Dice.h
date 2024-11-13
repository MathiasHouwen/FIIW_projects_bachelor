//
// Created by ebbew on 13-11-2024.
//

#ifndef CHATURAJI_DICE_H
#define CHATURAJI_DICE_H


#include "Piece.h"
#include <QSet>
#include <QPair>

class Dice {
public:
    struct Die{
        bool used{false};
        int number;
    };
    void doubleDobbel();
    Dice();
    bool allows(Piece::Type type);
    int getNumber(int die);
    bool isUsed(int die);
    void setUsed(Piece::Type type);
    QSet<Piece::Type> getAllowedTypes();
private:
    static constexpr Piece::Type typesMap[6][2] = {
            {Piece::Type::PAWN, Piece::Type::KING},
            {Piece::Type::BOAT, Piece::Type::BOAT},
            {Piece::Type::KNIGHT, Piece::Type::KNIGHT},
            {Piece::Type::ELEPH, Piece::Type::ELEPH},
            {Piece::Type::PAWN, Piece::Type::KING},
            {Piece::Type::ELEPH, Piece::Type::ELEPH}
    };
    Die dice[2];
};


#endif //CHATURAJI_DICE_H
