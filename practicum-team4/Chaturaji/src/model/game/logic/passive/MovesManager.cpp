// taakverdeling: zie h-file


#include "MovesManager.h"

QSet<ClassifiedMove> MovesManager::generateClassifiedMoves(Piece piece, QPoint location) {
    auto walkMoves = calculator.generatePossibleMoves(location, piece.getHomeSide(), piece.getType(), false);
    auto attackMoves = calculator.generatePossibleMoves(location, piece.getHomeSide(), piece.getType(), true);
    QSet<QPoint> destinations = {};
    QSet<ClassifiedMove> classifiedMoves{};
    for(auto moveLocation : walkMoves){
        if(!board.isEmptyAt(moveLocation)) continue; // board moet empty zijn
        auto specialType = classifySpecialMove(piece, moveLocation);
        classifiedMoves.insert({moveLocation, MoveType::NORMAL, specialType});
        destinations.insert(moveLocation);
    }
    for(auto moveLocation : attackMoves){
        if(destinations.contains(moveLocation)) continue; // dan is het al gehandled door de vorige loop
        if(board.isEmptyAt(moveLocation)) continue; // je moet iemand kunnen aanvallen -> niet empty
        if(board.getPieceAt(moveLocation)->getColor() == piece.getColor()) continue; // je kan niet je eigen kleur aanvallen
        auto specialType = classifySpecialMove(piece, moveLocation);
        classifiedMoves.insert({moveLocation, MoveType::ATTACK, specialType});
        destinations.insert(moveLocation);
    }
    return classifiedMoves;
}

SpecialMoveType MovesManager::classifySpecialMove(Piece piece, QPoint destination) {
    if(rulesChecker.validPawnPromotion(piece.getType(), piece.getHomeSide(), destination))
        return SpecialMoveType::PAWNPROMOTE;
    if(rulesChecker.validVrihannauka(piece.getType(), piece.getHomeSide(), destination))
        return SpecialMoveType::VRIHANNAUKA;
    if(rulesChecker.validSinhasana(piece.getType(), piece.getHomeSide(), destination))
        return SpecialMoveType::SINHASANA;
    return SpecialMoveType::NONE;
}

MovesManager::MovesManager(Board &board) : board(board) {}
