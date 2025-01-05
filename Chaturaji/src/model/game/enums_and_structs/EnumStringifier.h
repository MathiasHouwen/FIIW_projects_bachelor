//
// Created by ebbew on 5-1-2025.
//

#ifndef CHATURAJI_ENUMSTRINGIFIER_H
#define CHATURAJI_ENUMSTRINGIFIER_H


#include <QString>
#include "Color.h"
#include "HomeBoardSide.h"
#include "PieceType.h"

class EnumStringifier {
public:
    static QString cToString(Color color);
    static QString sToString(HomeBoardSide side);
    static QString tToString(PieceType type);
    static Color cFromString(QString color);
    static HomeBoardSide sFromString(QString side);
    static PieceType tFromString(QString type);
};


#endif //CHATURAJI_ENUMSTRINGIFIER_H
