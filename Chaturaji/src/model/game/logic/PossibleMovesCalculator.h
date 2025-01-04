//
// Created by ebbew on 7-10-2024.
//
// NIET AANGEPAST IN PRACTICUM 2


#ifndef CHATURAJI_POSSIBLEMOVESCALCULATOR_H
#define CHATURAJI_POSSIBLEMOVESCALCULATOR_H

#include <QSet>
#include <QPoint>
#include "../state/Board.h"
#include "../../enums_and_structs/Pattern.h"
#include "../../enums_and_structs/HomeBoardSide.h"

// BEREKENT ALLE POSSIBLE MOVES.
// HOUDT DUS GEEN REKENING MET OF ER EEN PIECE STAAT IN DE DESTINATION CELL
// HOUDT ER ENKEL REKENING MEE OM BVB NIET VERDER TE LOPEN DAN EEN OBSTAKEL (bij een infinite pattern)

class PossibleMovesCalculator {
private:
    // deze struct staat niet in een eigen file omdat die enkel private in deze class gebruikt wordt door een helper functie
    struct Patterns{
        Pattern move, attack;
        Patterns(const Pattern &move, const Pattern &attack);
        explicit Patterns(const Pattern &move);
    };
public:
    explicit PossibleMovesCalculator(Board& board);
    QSet<QPoint> generatePossibleMoves(QPoint location, HomeBoardSide side, PieceType pieceType, bool attack);
private:
    Board& board;
    QSet<QPoint> getPossibleMoves(const Pattern& pattern, QPoint cell);
    static QPoint sideToForwardDirection(HomeBoardSide side);
    static Patterns convertToPatterns(PieceType type, HomeBoardSide side);
    // creeert de possible moves voor 1 bepaalde diepte* (*zie cpp file -> generatePossibleMoves)
    QSet<QPoint> createPatternLayer(int d, const Pattern& pattern, QPoint cell, QVarLengthArray<bool>& validQuadrants);

};



#endif //CHATURAJI_POSSIBLEMOVESCALCULATOR_H
