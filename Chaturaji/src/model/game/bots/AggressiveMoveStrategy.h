//
// Created by robin on 3/01/2025.
//

#ifndef AGGRESSIVEMOVESTRATEGY_H
#define AGGRESSIVEMOVESTRATEGY_H



#include "MoveStrategy.h"
#include "../Game.h"

class AggressiveMoveStrategy : public MoveStrategy {
public:
    QPoint getNextMove(Game& game, const QSet<ClassifiedMove>& moves) override;
};



#endif //AGGRESSIVEMOVESTRATEGY_H
