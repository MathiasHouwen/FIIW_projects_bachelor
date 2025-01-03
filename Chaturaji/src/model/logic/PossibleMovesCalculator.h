//
// Created by ebbew on 7-10-2024.
//
// NIET AANGEPAST IN PRACTICUM 2


#ifndef CHATURAJI_POSSIBLEMOVESCALCULATOR_H
#define CHATURAJI_POSSIBLEMOVESCALCULATOR_H

#include <QSet>
#include <QPoint>
#include "../game/board/Board.h"
#include "../enums_and_structs/Pattern.h"


class PossibleMovesCalculator {
public:
    PossibleMovesCalculator(Board& board);
    // creeert alle mogelijke moves vanaf een cell (moves zijn bestemmingen, geen delta verplaatsingen)
    QSet<QPoint> getPossibleMoves(Pattern pattern, QPoint cell);
private:
    Board& board;
    // creeert de possible moves voor 1 bepaalde diepte* (*zie cpp file -> getPossibleMoves)
    QSet<QPoint> createPatternLayer(int d, Pattern pattern, QPoint cell, QVarLengthArray<bool>& validQuadrants);

};



#endif //CHATURAJI_POSSIBLEMOVESCALCULATOR_H
