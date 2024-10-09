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
private:
    int forward;
    QList<int> sideways;
    bool forwardOnly;
    bool infinite;
    QSet<QPoint> createPatternLayer(int d);
    Board& board;
public:
    PatternMover(int forward, const QList<int> &sideways, bool forwardOnly, bool infinite, Board& board);

    QSet<QPoint> possibleMoves();
};



#endif //CHATURAJI_PATTERNMOVER_H
