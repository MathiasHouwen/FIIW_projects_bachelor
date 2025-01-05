//
// Created by robin on 3/01/2025.
//

#include "PassiveMoveStrategy.h"

QPoint PassiveMoveStrategy::getNextMove(Game& game, const QSet<ClassifiedMove>& moves) {
    int minDistance = 0;
    QPoint calculated = {0,0};
    for(auto move : moves){
        if(move.destination.y() < minDistance){
            minDistance = move.destination.y();
            calculated = move.destination;
        }
    }
    return calculated;
}