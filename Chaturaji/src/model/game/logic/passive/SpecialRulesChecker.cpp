//
// Created by ebbew on 3-1-2025.
//

#include "SpecialRulesChecker.h"

bool SpecialRulesChecker::validPawnPromotion(PieceType type, HomeBoardSide homeSide, QPoint destination) {
    if(type != PieceType::PAWN) return false;
    // home side is de eigen home, niet de side waar die piece nu staat
    return homeSide == HomeBoardSide::BOTTOM && destination.y() == 7
    || homeSide == HomeBoardSide::TOP && destination.y() == 0
    || homeSide == HomeBoardSide::RIGHT && destination.x() == 0
    || homeSide == HomeBoardSide::LEFT && destination.x() == 7;
}

bool SpecialRulesChecker::validVrihannauka(PieceType type, HomeBoardSide homeSide, QPoint destination) {
    if(type != PieceType::BOAT) return false;
    std::vector<QPoint> topLeftCorners = {
            QPoint(destination.x() - 1, destination.y() - 1),
            QPoint(destination.x(), destination.y() - 1),
            QPoint(destination.x() - 1, destination.y()),
            QPoint(destination.x(), destination.y())
    };
    int counter = 0;
    for (const auto& corner : topLeftCorners) {
        if (isSquareFilledWithBoats(corner)) {
            counter ++;
        }
    }
    return counter == 3;
}

bool SpecialRulesChecker::isSquareFilledWithBoats(QPoint topLeft) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            QPoint cell(topLeft.x() + i, topLeft.y() + j);
            if (!Board::dimension.includes(cell) || board.isEmptyAt(cell) || board.getPieceAt(cell)->getType() != PieceType::BOAT) {
                return false;
            }
        }
    }
    return true;
}

bool SpecialRulesChecker::validSinhasana(PieceType type, HomeBoardSide homeSide, QPoint destination) {
    if(type != PieceType::KING) return false;
    QHash<QPoint, Color> map = {
            {QPoint(3, 7), Color::YELLOW},
            {QPoint(7, 4), Color::GREEN},
            {QPoint(0, 3), Color::BLUE},
            {QPoint(4, 0), Color::RED}
    };
    return homeSide != HomeBoardSide::BOTTOM && destination != QPoint{4,3}
           || homeSide != HomeBoardSide::TOP && destination != QPoint{3,7}
           || homeSide != HomeBoardSide::RIGHT && destination != QPoint{7,4}
           || homeSide != HomeBoardSide::LEFT && destination != QPoint{0,3};
}

SpecialRulesChecker::SpecialRulesChecker(Board &board) : board(board) {}
