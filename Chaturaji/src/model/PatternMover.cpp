//
// Created by ebbew on 7-10-2024.
//

#include "PatternMover.h"

PatternMover::PatternMover(bool straight, bool diagonal, bool forwardOnly, int distance, int offset) : straight(
        straight), diagonal(diagonal), forwardOnly(forwardOnly), distance(distance), offset(offset) {}

QSet<QPoint> PatternMover::possibleMoves() {
    QSet<QPoint> moves;
    return moves;
}
