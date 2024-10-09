//
// Created by ebbew on 7-10-2024.
//

#include "PatternMover.h"

PatternMover::PatternMover(int forward, const QList<int> &sideways, bool forwardOnly, bool infinite)
    : forward(forward),
    sideways(sideways),
    forwardOnly(forwardOnly),
    infinite(infinite) {}

QSet<QPoint> PatternMover::possibleMoves() {
    if(infinite){
        QSet<QPoint> moves;
        for(int distance = 1; distance <= 8/forward; distance++){
            moves.unite(createPatternLayer(distance));
        }
        return moves;
    }
    return createPatternLayer(forward);
}

QSet<QPoint> PatternMover::createPatternLayer(int distance) {
    //TODO: Moet nog stoppen na bostsing tegen piece indien infinite
    //cell met piece included, game kiest of dat een move of attach wordt.
    QSet<QPoint> moves;
    bool *validQuadrants = new bool[4*sideways.size()];
    for(int sw : sideways){
        int quadrant = 0;
        for(int toggler : {0,1}){
            for(int mirrorer : {-1,1}){
                int x = distance * mirrorer * (toggler ? forward : sw);
                int y = distance * mirrorer * (toggler ? sw : -forward);
                moves.insert({x,y});
                quadrant++;
                if(forwardOnly) break;
            }
            if(forwardOnly) break;
        }
    }
    delete[] validQuadrants;
    return moves;
}
