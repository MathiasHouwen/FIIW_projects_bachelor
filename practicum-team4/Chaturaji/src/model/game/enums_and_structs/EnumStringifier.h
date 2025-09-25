//practicum 3:
// - Ebbe: class aangemaakt en geschreven
// doel: vertalen van enums centraliseren
//     -> vertalen hoorde niet thuis in sommige model classes
//          bvb colors vertalen in player class
//     -> bij gebruikende class zetten kan ook niet want er zijn meerdere die dezelfde enum gebruiken -> niet DRY om overal te zetten

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
