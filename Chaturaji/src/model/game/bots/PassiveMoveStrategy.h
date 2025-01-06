//
// Created by robin on 3/01/2025.
//

#ifndef PASSIVEMOVESTRATEGY_H
#define PASSIVEMOVESTRATEGY_H

#include "MoveStrategy.h"
#include "../Game.h"

class PassiveMoveStrategy : public MoveStrategy {
public:
    QPoint getNextMove(Game& game, const QSet<ClassifiedMove>& moves) override;
    QPoint getNextSelectedCell(Game& game, const QSet<QPoint>& selectables) override;
};

#endif //PASSIVEMOVESTRATEGY_H
