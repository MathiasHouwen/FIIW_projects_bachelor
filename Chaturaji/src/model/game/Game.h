//
// Created by ebbew on 5-1-2025.
//

#ifndef CHATURAJI_GAME_H
#define CHATURAJI_GAME_H


#include "state/GameState.h"
#include "logic/passive/MovesManager.h"
#include "logic/BoardQuerier.h"
#include "logic/active/SpecialRulesExecutor.h"

class Game {
private:
    GameState gameState;
    MovesManager movesManager;
    BoardQuerier querier;
    SpecialRulesExecutor rulesExecutor;
    void executeClassifiedMove(QPoint from, ClassifiedMove move, PieceType pawnPromoteType = PieceType::PAWN);
    static int pieceTypeToScore(PieceType type);
public:
    Game();
    bool doMove(QPoint from, QPoint to, PieceType pawnPromoteType);
};


#endif //CHATURAJI_GAME_H
