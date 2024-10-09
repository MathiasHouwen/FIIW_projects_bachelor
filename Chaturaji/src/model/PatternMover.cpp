//
// Created by ebbew on 7-10-2024.
//

#include <qvarlengtharray.h>
#include "PatternMover.h"

PatternMover::PatternMover(Board& board) : board(board) {}

QSet<QPoint> PatternMover::getPossibleMoves(Pattern pattern, QPoint cell) {
    if(pattern.infinite){
        QSet<QPoint> moves;
        for(int distance = 1; distance <= board.getSize()/pattern.forward; distance++){
            moves.unite(createPatternLayer(distance, pattern, cell));
        }
        return moves;
    }
    return createPatternLayer(1, pattern, cell);
}

QSet<QPoint> PatternMover::createPatternLayer(int distance, Pattern pattern, QPoint cell) {

    QSet<QPoint> moves;
    QVarLengthArray<bool> validQuadrants(4*pattern.sideways.size(), true);
    for(int sw : pattern.sideways){
        int quadrant = 0;
        for(int toggler : {0,1}){
            for(int mirrorer : {-1,1}){
                // indien de pattern oneindig in een richting kan bewegen:
                // mag niet verder bewegen als die in die richting (quadrant) al
                // gebotst is tegen een piece -> quadrant valid = false
                if(validQuadrants[quadrant]){
                    int x = cell.x() + distance * mirrorer * (toggler ? pattern.forward : sw);
                    int y = cell.y() + distance * mirrorer * (toggler ? sw : -pattern.forward);
                    QPoint newCell = {x,y};
                    if(board.isInRange(newCell)){
                        // als cell al bezet is mag je daarna niet verder bewegen in dat quadrant
                        if(!board.isCellEmpty(newCell))
                            validQuadrants[quadrant] = false;
                        // wel sowieso adden want als huidige bezet is kan je wel die piece aanvallen
                        moves.insert(newCell);
                    }
                }
                quadrant++;
                if(pattern.forwardOnly) break;
            }
            if(pattern.forwardOnly) break;
        }
    }
    return moves;
}
