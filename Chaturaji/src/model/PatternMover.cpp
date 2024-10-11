//
// Created by ebbew on 7-10-2024.
//

#include <qvarlengtharray.h>
#include <iostream>
#include "PatternMover.h"

PatternMover::PatternMover(Board& board) : board(board) {}

QSet<QPoint> PatternMover::getPossibleMoves(Pattern pattern, QPoint cell) {
    QVarLengthArray<bool> validQuadrants(4*pattern.sideways.size(), true);
    if(pattern.infinite){
        QSet<QPoint> moves;
        for(int distance = 1; distance <= board.getSize()/pattern.forward; distance++){
            moves.unite(createPatternLayer(distance, pattern, cell, validQuadrants));
        }
        return moves;
    }
    return createPatternLayer(1, pattern, cell, validQuadrants);
}

QSet<QPoint> PatternMover::createPatternLayer(int distance, Pattern pattern, QPoint cell, QVarLengthArray<bool>& validQuadrants) {
    QSet<QPoint> moves;
    for(int sw : pattern.sideways){
        int quadrant = 0;
        const QPoint dirs[] = {{0,1},{0,-1},{1,0},{-1,0}};
        for(QPoint dir : dirs){
            // indien de pattern oneindig in een richting kan bewegen:
            // mag niet verder bewegen als die in die richting (quadrant) al
            // gebotst is tegen een piece -> quadrant valid = false
            bool isPlayerDirection = pattern.forwardOnly && pattern.forwardDirection == dir;
            std::cout << isPlayerDirection << std::endl;
            if(validQuadrants[quadrant] && isPlayerDirection){
                //int x = cell.x() + distance * mirrorer * (toggler ? pattern.forward : sw);
                //int y = cell.y() + distance * mirrorer * (toggler ? sw : -pattern.forward);
                int x = cell.x() + distance * ( dir.x() * pattern.forward + dir.y() * sw );
                int y = cell.y() + distance * ( dir.y() * pattern.forward + dir.x() * sw );;
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
        }
    }
    return moves;
}
