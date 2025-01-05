//
// Created by robin on 19/12/2024.
//

#ifndef BOT_H
#define BOT_H
#include <utility>

#include "MoveStrategy.h"


class Bot : public Player {
public:
    Bot(Color color, std::shared_ptr<MoveStrategy> strategy);
    QPoint getNextMove(Game& game, const QSet<QPoint>& moves);

private:
    std::shared_ptr<MoveStrategy> strategy;
};



#endif //BOT_H
