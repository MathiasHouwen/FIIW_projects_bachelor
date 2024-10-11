//
// Created by ebbew on 7-10-2024.
//

#ifndef CHATURAJI_PATTERNMOVER_H
#define CHATURAJI_PATTERNMOVER_H

#include <QSet>
#include <QPoint>
#include "Board.h"

//
// Boat         2F2S
// Horse        2F1S
// Elephant     -1F0S
// King         1F1S
// Pawn
//




class PatternMover {
public:
    struct Pattern{
        int forward;
        QList<int> sideways;
        bool forwardOnly;
        bool infinite;
        QPoint forwardDirection;
    };
    PatternMover(Board& board);
    QSet<QPoint> getPossibleMoves(Pattern pattern, QPoint cell);
private:
    Pattern pattern;
    QSet<QPoint> createPatternLayer(int d, Pattern pattern, QPoint cell, QVarLengthArray<bool>& validQuadrants);
    Board& board;
};



#endif //CHATURAJI_PATTERNMOVER_H
