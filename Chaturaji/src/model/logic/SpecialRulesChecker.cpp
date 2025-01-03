//
// Created by ebbew on 3-1-2025.
//

#include "SpecialRulesChecker.h"

bool SpecialRulesChecker::validPawnPromotion(PieceType type, HomeBoardSide homeSide, QPoint destination) {
    if(type != PieceType::PAWN) return false;
    //TODO
    return false;
}

bool SpecialRulesChecker::validVrihannauka(PieceType type, HomeBoardSide homeSide, QPoint destination) {
    if(type != PieceType::BOAT) return false;
    //TODO
    return false;
}

bool SpecialRulesChecker::validSinhasana(PieceType type, HomeBoardSide homeSide, QPoint destination) {
    if(type != PieceType::KING) return false;
    //TODO
    return false;
}

SpecialRulesChecker::SpecialRulesChecker(Board &board) : board(board) {}
