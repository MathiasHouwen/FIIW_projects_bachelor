//
// Created by ebbew on 13-11-2024.
//

//volledig door ebbe, nieuw sinds practicum 2
// doel: complexiteit van Game class (vooral Game::movePiece()) verlagen door dobbelsteen logica apart te zetten
// deze class houdt zelf 2 dice bij, kan ze rollen
// kan checken of een piece type geldig is, zodat je niet specifiek per die hoeft te vergelijken


#ifndef CHATURAJI_DICE_H
#define CHATURAJI_DICE_H


#include "../enums_and_structs/PieceType.h"
#include <QSet>
#include <QPair>

class Dice {
public:
    void doubleDobbel();
    Dice();
    bool allowsType(PieceType type); // kijkt of dit piece type geldig is volgens de 2 dobbelstenen
    int asNumber(int die);
    bool isUsed(int die);
    void setUsed(PieceType type);
    QSet<PieceType> getAllowedTypes(); // geeft alle alowed types terug (gebruikt door view. game hoeft alleen te valideren met allowsType)
private:
    struct Die{
        bool used{false}; // gebruikte dobbelsteen zal zichzelf ongeldig maken
        int number; // nummer van dobbelsteen om in view te gebruiken
    };
    // QSet kan niet const of constexpr in literar declaratie
    Die dice[2];
    static QSet<PieceType> numberToTypes(int number);
};


#endif //CHATURAJI_DICE_H
