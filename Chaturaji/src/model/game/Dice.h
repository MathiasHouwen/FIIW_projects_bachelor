//
// Created by ebbew on 13-11-2024.
//

//volledig door ebbe, nieuw sinds practicum 2
// doel: complexiteit van Game class (vooral Game::movePiece()) verlagen door dobbelsteen logica apart te zetten
// deze class houdt zelf 2 dice bij, kan ze rollen
// kan checken of een piece type geldig is, zodat je niet specifiek per die hoeft te vergelijken


#ifndef CHATURAJI_DICE_H
#define CHATURAJI_DICE_H


#include "board/Piece.h"
#include <QSet>
#include <QPair>

class Dice {
public:
    struct Die{
        bool used{false}; // gebruikte dobbelsteen zal zichzelf ongeldig maken
        int number; // nummer van dobbelsteen om in view te gebruiken
    };
    void doubleDobbel();
    Dice();
    bool allows(Piece::Type type); // kijkt of dit piece type geldig is volgens de 2 dobbelstenen
    int getNumber(int die);
    bool isUsed(int die);
    void setUsed(Piece::Type type);
    QSet<Piece::Type> getAllowedTypes(); // geeft alle alowed types terug (gebruikt door view. game hoeft alleen te valideren met allows)
private:
    // QSet kan niet const of constexpr in literar declaratie
    static inline QSet<Piece::Type> typesMap[6] = {
            {Piece::Type::PAWN, Piece::Type::KING},
            {Piece::Type::BOAT},
            {Piece::Type::KNIGHT},
            {Piece::Type::ELEPH},
            {Piece::Type::PAWN, Piece::Type::KING},
            {Piece::Type::ELEPH}
    };
    Die dice[2];
};


#endif //CHATURAJI_DICE_H
