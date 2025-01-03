//
// Created by robin on 3/01/2025.
//

#ifndef PASSIVEMOVESTRATEGY_H
#define PASSIVEMOVESTRATEGY_H

#include "MoveStrategy.h"
#include "../board/Piece.h"
#include "../Game.h"

class PassiveMoveStrategy : public MoveStrategy {
public:
    QPoint getNextMove(Game& game, const QSet<QPoint>& moves) override;
};

#endif //PASSIVEMOVESTRATEGY_H
