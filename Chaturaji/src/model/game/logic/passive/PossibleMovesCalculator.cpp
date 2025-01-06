// taakverdeling: zie h-file



#include <qvarlengtharray.h>
#include <iostream>
#include "PossibleMovesCalculator.h"

PossibleMovesCalculator::PossibleMovesCalculator(Board& board) : board(board) {}

QSet<QPoint> PossibleMovesCalculator::getPossibleMoves(const Pattern& pattern, QPoint cell) {
    // Elke richting waarin een piece een movePiece kan doen is een quadrant.
    // indien er een obstakel is, zal die quadrant invalid worden,
    // waardoor je niet verder kan lopen in die richting
    QVarLengthArray<bool> validQuadrants(4*pattern.sideways.size(), true);

    if(pattern.infinite){
        // in geval van infinite, moeten er moves zijn op elke diepte
        // (afstand vanaf de speler tot aan de bord randen)
        // is niet aantal cellen, maar 1 dieptelaag heeft de grootte van de moves in die laag
        QSet<QPoint> moves;
        // voeg moves samen van alle diepten (probeert max mogelijke diepte ondanks huidige positie, moves buiten bord worden later genegeerd)
        for(int distance = 1; distance <= board.dimension.getSize()/pattern.forward; distance++){
            moves.unite(createPatternLayer(distance, pattern, cell, validQuadrants));
        }
        return moves;
    }
    // als het pattroon niet infinite is, is diepte 1
    return createPatternLayer(1, pattern, cell, validQuadrants);
}

QSet<QPoint> PossibleMovesCalculator::createPatternLayer(int distance, const Pattern& pattern, QPoint cell, QVarLengthArray<bool>& validQuadrants) {
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

                if(board.dimension.includes(newCell)){
                    // als cell al bezet is mag je daarna niet verder bewegen in dat quadrant
                    // de cell zelf telt wel nog mee, want je mag mogelijks een piece aanvallen
                    if(!board.isEmptyAt(newCell))
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

QSet<QPoint> PossibleMovesCalculator::generatePossibleMoves(QPoint location, HomeBoardSide side, PieceType pieceType, bool attack) {
    Patterns patterns = convertToPatterns(pieceType, side);
    Pattern pattern = attack ? patterns.attack : patterns.move;
    return getPossibleMoves(pattern, location);
}

QPoint PossibleMovesCalculator::sideToForwardDirection(HomeBoardSide side) {
    switch (side) {
        case HomeBoardSide::LEFT: return {1,0};
        case HomeBoardSide::RIGHT: return {-1,0};
        case HomeBoardSide::TOP: return {0,-1};
        case HomeBoardSide::BOTTOM: return {0,1};
    }
}

PossibleMovesCalculator::Patterns PossibleMovesCalculator::convertToPatterns(PieceType type, HomeBoardSide side) {
    QPoint direction = sideToForwardDirection(side);
    switch (type) {
        case PieceType::BOAT:
            return Patterns({2, {2}, false, false, direction});
        case PieceType::ELEPHANT:
            return Patterns({1, {0}, false, true, direction});
        case PieceType::HORSE:
            return Patterns({2, {-1, 1}, false, false, direction});
        case PieceType::KING:
            return Patterns({1, {0,1}, false, false, direction});
        case PieceType::PAWN:
            return Patterns(
                    {1, {0}, true, false, direction},
                    {1, {-1,1}, true, false, direction});
    }
}

PossibleMovesCalculator::Patterns::Patterns(const Pattern &move, const Pattern &attack) : move(move), attack(attack) {}
PossibleMovesCalculator::Patterns::Patterns(const Pattern &move) : move(move), attack(move) {}
