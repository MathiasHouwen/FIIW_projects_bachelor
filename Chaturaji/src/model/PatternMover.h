//
// Created by ebbew on 7-10-2024.
//

#ifndef CHATURAJI_PATTERNMOVER_H
#define CHATURAJI_PATTERNMOVER_H

#include <QSet>
#include <QPoint>
#include "Board.h"
#include "Pattern.h"


class PatternMover {
public:
    PatternMover(Board& board);
    // creeert alle mogelijke moves vanaf een cell (moves zijn bestemmingen, geen delta verplaatsingen)
    QSet<QPoint> getPossibleMoves(Pattern pattern, QPoint cell);
private:
    Board& board;
    // creeert de possible moves voor 1 bepaalde diepte* (*zie cpp file -> getPossibleMoves)
    QSet<QPoint> createPatternLayer(int d, Pattern pattern, QPoint cell, QVarLengthArray<bool>& validQuadrants);

};



#endif //CHATURAJI_PATTERNMOVER_H
