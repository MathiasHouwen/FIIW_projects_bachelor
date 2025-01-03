//
// Created by ebbew on 3-1-2025.
//

#ifndef CHATURAJI_MOVESMANAGER_H
#define CHATURAJI_MOVESMANAGER_H


#include "../enums_and_structs/ClassifiedMove.h"
#include "../game/board/Piece.h"
#include "../game/board/Board.h"
#include "PossibleMovesCalculator.h"
#include "SpecialRulesChecker.h"

#include <QSet>

class MovesManager {
private:
    Board& board;
    PossibleMovesCalculator calculator{board};
    SpecialRulesChecker rulesChecker{board};
public:
    QSet<ClassifiedMove> generateClassifiedMoves(Piece piece);
};


#endif //CHATURAJI_MOVESMANAGER_H
