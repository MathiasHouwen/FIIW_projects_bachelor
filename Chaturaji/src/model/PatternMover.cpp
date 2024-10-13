//
// Created by ebbew on 7-10-2024.
//

#include <qvarlengtharray.h>
#include <iostream>
#include "PatternMover.h"

PatternMover::PatternMover(Board& board) : board(board) {}

QSet<QPoint> PatternMover::getPossibleMoves(Pattern pattern, QPoint cell) {
    // Elke richting waarin een piece een move kan doen is een quadrant.
    // indien er een obstakel is, zal die quadrant invalid worden,
    // waardoor je niet verder kan lopen in die richting
    QVarLengthArray<bool> validQuadrants(4*pattern.sideways.size(), true);

    if(pattern.infinite){
        // in geval van infinite, moeten er moves zijn op elke diepte
        // (afstand vanaf de speler tot aan de bord randen)
        // is niet aantal cellen, maar 1 dieptelaag heeft de grootte van de moves in die laag
        QSet<QPoint> moves;
        // voeg moves samen van alle diepten (probeert max mogelijke diepte ondanks huidige positie, moves buiten bord worden later genegeerd)
        for(int distance = 1; distance <= board.getSize()/pattern.forward; distance++){
            moves.unite(createPatternLayer(distance, pattern, cell, validQuadrants));
        }
        return moves;
    }
    // als het pattroon niet infinite is, is diepte 1
    return createPatternLayer(1, pattern, cell, validQuadrants);
}

QSet<QPoint> PatternMover::createPatternLayer(int distance, Pattern pattern, QPoint cell, QVarLengthArray<bool>& validQuadrants) {
    QSet<QPoint> moves;
    for(int sw : pattern.sideways){
        int quadrant = 0;
        // eenheidsvectoren voor elke richting
        const QPoint dirs[] = {{0,1},{0,-1},{1,0},{-1,0}};
        for(QPoint dir : dirs){
            // indien de pattern oneindig in een richting kan bewegen:
            // mag niet verder bewegen als die in die richting (quadrant) al
            // gebotst is tegen een piece -> quadrant valid = false
            // daarnaast zijn bij forwaldOnly alle richtingen buiten de speler richting ook geblokkeerd
            bool isPlayerDirection = !pattern.forwardOnly || pattern.forwardDirection == dir;
            if(validQuadrants[quadrant] && isPlayerDirection){
                // voor x is foward een verplaatsing in de x van de richting, en sideways een y verplaatsing
                // voor y vice versa
                int x = cell.x() + distance * ( dir.x() * pattern.forward + dir.y() * sw );
                int y = cell.y() + distance * ( - dir.y() * pattern.forward + dir.x() * sw );
                QPoint newCell = {x,y};

                if(board.isInRange(newCell)){
                    // als cell al bezet is mag je daarna niet verder bewegen in dat quadrant
                    // de cell zelf telt wel nog mee, want je mag mogelijks een piece aanvallen
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
