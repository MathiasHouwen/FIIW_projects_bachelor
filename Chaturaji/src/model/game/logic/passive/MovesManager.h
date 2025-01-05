//
// Created by ebbew on 3-1-2025.
//

#ifndef CHATURAJI_MOVESMANAGER_H
#define CHATURAJI_MOVESMANAGER_H


#include "../../enums_and_structs/ClassifiedMove.h"
#include "../identities/Piece.h"
#include "../../state/Board.h"
#include "PossibleMovesCalculator.h"
#include "SpecialRulesChecker.h"

#include <QSet>

class MovesManager {
private:
    Board& board;
    PossibleMovesCalculator calculator{board};
    SpecialRulesChecker rulesChecker{board};
    SpecialMoveType classifySpecialMove(Piece piece, QPoint destination);
public:
    QSet<ClassifiedMove> generateClassifiedMoves(Piece piece, QPoint location);
};


#endif //CHATURAJI_MOVESMANAGER_H
