// taakverdeling: zie h-file


#include "SpecialRulesChecker.h"

bool SpecialRulesChecker::validPawnPromotion(PieceType type, HomeBoardSide homeSide, QPoint destination) {
    if(type != PieceType::PAWN) return false;
    // home side is de eigen home, niet de side waar die piece nu staat
    return homeSide == HomeBoardSide::BOTTOM && querier.isPointFromBoardSideEdge(destination, HomeBoardSide::TOP)
    || homeSide == HomeBoardSide::TOP && querier.isPointFromBoardSideEdge(destination, HomeBoardSide::BOTTOM)
    || homeSide == HomeBoardSide::LEFT && querier.isPointFromBoardSideEdge(destination, HomeBoardSide::RIGHT)
    || homeSide == HomeBoardSide::BOTTOM && querier.isPointFromBoardSideEdge(destination, HomeBoardSide::LEFT);
}

bool SpecialRulesChecker::validVrihannauka(PieceType type, HomeBoardSide homeSide, QPoint destination) {
    if(type != PieceType::BOAT) return false;

    std::vector<QPoint> possibleTopLeftCorners = {
            QPoint(destination.x() - 1, destination.y() - 1),
            QPoint(destination.x(), destination.y() - 1),
            QPoint(destination.x() - 1, destination.y()),
            destination
    };
    for (const auto& corner : possibleTopLeftCorners) {
         if(isSquareFilledWithBoats(corner, destination)){
             return true;
         }
    }
    return false;
}

bool SpecialRulesChecker::isSquareFilledWithBoats(QPoint topLeft, QPoint destination) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            QPoint cell(topLeft.x() + i, topLeft.y() + j);
            if(cell == destination) continue;
            if (!Board::dimension.includes(cell)
                || board.isEmptyAt(cell)
                || board.getPieceAt(cell)->getType() != PieceType::BOAT) {
                return false;
            }
        }
    }
    return true;
}

bool SpecialRulesChecker::validSinhasana(PieceType type, HomeBoardSide homeSide, QPoint destination) {
    if(type != PieceType::KING) return false;
    QHash<QPoint, HomeBoardSide> kingCells = {
            {QPoint(4, 7), HomeBoardSide::BOTTOM},
            {QPoint(7, 3), HomeBoardSide::RIGHT},
            {QPoint(0, 4), HomeBoardSide::LEFT},
            {QPoint(3, 0), HomeBoardSide::TOP}
    };
    if(!kingCells.contains(destination)) return false;
    return kingCells[destination] != homeSide; // mag niet van je eigen side zijn
}

SpecialRulesChecker::SpecialRulesChecker(Board &board) : board(board), querier(board) {}
