//
// Created by ebbew on 9-10-2024.
//

//practicum 2: enkel cell (+get/set) toegevoegd door ebbe

#ifndef CHATURAJI_BADPIECECLASS_H
#define CHATURAJI_BADPIECECLASS_H

#include <QPoint>
#include "../Player.h"
#include "../../enums_and_structs/Pattern.h"
class Player; // forward decl om circular dependency te voorkomen
class BadPieceClass {
public:
    // types
    // dobbelsteen gebruikt ook type, zonder piece. Used is daarbij de dobbelsteen keuze die je al gebruikt hebt
    enum class Type {PAWN, BOAT, ELEPH, KNIGHT, KING, USED};

    const Pattern &getWalkPattern() const;
    const Pattern &getAttackPattern() const;
    explicit BadPieceClass() = default;
    BadPieceClass(Type type, QPoint direction, Player& player, QPoint cell = {-1, -1});

    // getters
    Type getType() const;
    int getScoreValue() const;
    Player &getPlayer() const;
    QString getColorName();

    const QPoint &getCell() const;
    void setCell(const QPoint &cell);

    static QString getTypeName(Type type); // vertaalt type naar string naam
    QString getTypeName();
    static BadPieceClass::Type getTypeFromName(const QString& typestr); // vertaalt string naam naar type
    bool operator>(const BadPieceClass &other) const;
    bool operator<(const BadPieceClass &other) const;

private:
    void init(Pattern pattern, int ScoreValue); // initialiseer type specifieke kenmerken
    Pattern walkPattern;  // loop patroon
    Pattern attackPattern; // aanval patroon (bvb pawn kan diagonaal aanvallen maar enkel rechtdoor lopen)
    Type type;
    int scoreValue; // hoeveel score een kill kan opleveren
    Player& player; // eigenaar
    QPoint cell;
};




#endif //CHATURAJI_BADPIECECLASS_H
