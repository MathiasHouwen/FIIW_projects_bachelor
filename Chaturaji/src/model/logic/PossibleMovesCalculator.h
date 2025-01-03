//
// Created by ebbew on 7-10-2024.
//
// NIET AANGEPAST IN PRACTICUM 2


#ifndef CHATURAJI_POSSIBLEMOVESCALCULATOR_H
#define CHATURAJI_POSSIBLEMOVESCALCULATOR_H

#include <QSet>
#include <QPoint>
#include "../game/board/Board.h"
#include "../enums_and_structs/Pattern.h"
#include "../enums_and_structs/HomeBoardSide.h"


class PossibleMovesCalculator {
private:
    struct Patterns{
        Pattern move, attack;
        Patterns(const Pattern &move, const Pattern &attack);
        explicit Patterns(const Pattern &move);
    };
public:
    explicit PossibleMovesCalculator(Board& board);
    QSet<QPoint> getPossibleMoves(QPoint location, HomeBoardSide side, PieceType pieceType);
private:
    Board& board;
    QSet<QPoint> getPossibleMoves(const Pattern& pattern, QPoint cell);
    static QPoint sideToForwardDirection(HomeBoardSide side);
    static Patterns convertToPatterns(PieceType type, HomeBoardSide side);
    // creeert de possible moves voor 1 bepaalde diepte* (*zie cpp file -> getPossibleMoves)
    QSet<QPoint> createPatternLayer(int d, const Pattern& pattern, QPoint cell, QVarLengthArray<bool>& validQuadrants);

};



#endif //CHATURAJI_POSSIBLEMOVESCALCULATOR_H
