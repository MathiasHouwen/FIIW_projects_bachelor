//
// Created by ebbew on 9-10-2024.
//

#ifndef CHATURAJI_PIECE_H
#define CHATURAJI_PIECE_H


#include <QPoint>
#include "Player.h"
#include "Pattern.h"
#include <qobjectdefs.h>

class Piece {
public:
    // types
    // dobbelsteen gebruikt ook type, zonder piece. Used is daarbij de dobbelsteen keuze die je al gebruikt hebt
    enum class Type {PAWN, BOAT, ELEPH, KNIGHT, KING, USED};

    QPoint direction; // enkel voor JSON. direction zit standaard in de pattern van een piece
    const Pattern &getWalkPattern() const;
    const Pattern &getAttackPattern() const;

    Piece(Type type, QPoint direction, Player& player);

    // getters
    Type getType() const;
    int getScoreValue() const;
    static std::vector<Piece::Type> getTypeFromDobbel(int number);
    Player &getPlayer() const;
    QString getShortName();
    QString getColorName();

    static QString getTypeName(Type type); // vertaalt type naar string naam
    static Piece::Type getTypeFromName(const QString& typestr); // vertaalt string naam naar type

private:
    void init(Pattern pattern, int ScoreValue); // initialiseer type specifieke kenmerken
    Pattern walkPattern;  // loop patroon
    Pattern attackPattern; // aanval patroon (bvb pawn kan diagonaal aanvallen maar enkel rechtdoor lopen)
    Type type;
    int scoreValue; // hoeveel score een kill kan opleveren
    Player& player; // eigenaar
};


#endif //CHATURAJI_PIECE_H
