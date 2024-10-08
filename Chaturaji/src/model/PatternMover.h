//
// Created by ebbew on 7-10-2024.
//

#ifndef CHATURAJI_PATTERNMOVER_H
#define CHATURAJI_PATTERNMOVER_H

#include <QSet>
#include <QPoint>

//
// Boat         2F2S
// Horse        2F1S
// Elephant     -1F0S
// King         1F1S
// Pawn
//




class PatternMover {
private:
    bool straight;
    bool diagonal;
    bool forwardOnly;
    int distance;
    int offset;
public:
    PatternMover(bool straight, bool diagonal, bool forwardOnly, int distance, int offset);
    QSet<QPoint> possibleMoves();
};


#endif //CHATURAJI_PATTERNMOVER_H
