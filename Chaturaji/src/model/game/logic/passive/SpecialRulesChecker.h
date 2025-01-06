//
// Created by ebbew on 3-1-2025.
//

#ifndef CHATURAJI_SPECIALRULESCHECKER_H
#define CHATURAJI_SPECIALRULESCHECKER_H


#include <QPoint>
#include "../../enums_and_structs/PieceType.h"
#include "../../enums_and_structs/HomeBoardSide.h"
#include "../../state/Board.h"
#include "../BoardQuerier.h"

class SpecialRulesChecker {
private:
    Board& board;
    BoardQuerier querier;
public:
    explicit SpecialRulesChecker(Board &board);

public:
    bool validPawnPromotion(PieceType type, HomeBoardSide homeSide, QPoint destination);
    bool validVrihannauka(PieceType type, HomeBoardSide homeSide, QPoint destination); // aka die boat dinges
    bool validSinhasana(PieceType type, HomeBoardSide homeSide, QPoint destination) ; // aka die king dinges
    bool isSquareFilledWithBoats(QPoint topLeft, QPoint destination);
};


#endif //CHATURAJI_SPECIALRULESCHECKER_H
