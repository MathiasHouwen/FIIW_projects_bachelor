//
// Created by ebbew on 5-1-2025.
//

#ifndef CHATURAJI_SPECIALRULESEXECUTOR_H
#define CHATURAJI_SPECIALRULESEXECUTOR_H


#include "../../state/Board.h"
#include "../BoardQuerier.h"
#include "../../state/identities/Player.h"

class SpecialRulesExecutor {
private:
    Board& board;
    BoardQuerier querier;
public:
    explicit SpecialRulesExecutor(Board &board);
    void promotePawn(QPoint location, PieceType newPieceType);
    void vrihannauka(QPoint location); // aka die boat dinges
    void sinhasana(QPoint location); // aka die king dinges
    void captureBoats(QPoint topLeft, Color ownColor);
};


#endif //CHATURAJI_SPECIALRULESEXECUTOR_H
