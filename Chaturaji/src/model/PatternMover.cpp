//
// Created by ebbew on 7-10-2024.
//

#include <qvarlengtharray.h>
#include "PatternMover.h"

PatternMover::PatternMover(int forward, const QList<int> &sideways, bool forwardOnly, bool infinite, Board& board)
    : forward(forward),
    sideways(sideways),
    forwardOnly(forwardOnly),
    infinite(infinite),
    board(board) {}

QSet<QPoint> PatternMover::possibleMoves() {
    if(infinite){
        QSet<QPoint> moves;
        for(int distance = 1; distance <= board.getSize()/forward; distance++){
            moves.unite(createPatternLayer(distance));
        }
        return moves;
    }
    return createPatternLayer(forward);
}

QSet<QPoint> PatternMover::createPatternLayer(int distance) {
    QSet<QPoint> moves;
    QVarLengthArray<bool> validQuadrants(4*sideways.size(), true);
    for(int sw : sideways){
        int quadrant = 0;
        for(int toggler : {0,1}){
            for(int mirrorer : {-1,1}){
                // indien de pattern oneindig in een richting kan bewegen:
                // mag niet verder bewegen als die in die richting (quadrant) al
                // gebotst is tegen een piece -> quadrant valid = false
                if(validQuadrants[quadrant]){
                    int x = distance * mirrorer * (toggler ? forward : sw);
                    int y = distance * mirrorer * (toggler ? sw : -forward);
                    QPoint cell = {x,y};
                    // als cell al bezet is mag je daarna niet verder bewegen in dat quadrant
                    if(!board.isCellEmpty(cell))
                        validQuadrants[quadrant] = false;
                    // wel sowieso adden want als huidige bezet is kan je wel die piece aanvallen
                    moves.insert(cell);
                }
                quadrant++;
                if(forwardOnly) break;
            }
            if(forwardOnly) break;
        }
    }
    return moves;
}
