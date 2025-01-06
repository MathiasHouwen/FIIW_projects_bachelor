//practicum 3:
// - Ebbe: class gemaakt en geschreven
// doel: enkel game logica bevatten ( het uitvoeren van een move ).
// logica is gedeeltelijk afkomstig van de oude Controller en Game classes

#ifndef CHATURAJI_GAME_H
#define CHATURAJI_GAME_H


#include "logic/passive/MovesManager.h"
#include "logic/BoardQuerier.h"
#include "logic/active/SpecialRulesExecutor.h"
#include "state/GameState.h"

class Game {
private:
    GameState gameState{};
    MovesManager movesManager;
    BoardQuerier querier;
    SpecialRulesExecutor rulesExecutor;
    void executeClassifiedMove(QPoint from, ClassifiedMove move, PieceType pawnPromoteType = PieceType::PAWN);
    static int pieceTypeToScore(PieceType type);
public:
    Game();
    GameState &getGameState();
    bool doMove(QPoint from, QPoint to, PieceType pawnPromoteType);
    bool isCellAllowedToBePicked(QPoint cell);
};


#endif //CHATURAJI_GAME_H
