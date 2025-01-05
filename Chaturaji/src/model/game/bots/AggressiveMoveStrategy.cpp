//
// Created by robin on 3/01/2025.
//

#include "AggressiveMoveStrategy.h"

QPoint AggressiveMoveStrategy::getNextMove(Game& game, const QSet<QPoint>& moves) {
    int minDistance = 0;
    QPoint calculated = {0,0};
    for(auto move : moves){
        if(move.y() > minDistance){
            minDistance = move.y();
            calculated = move;
        }
    }
    return calculated;
}