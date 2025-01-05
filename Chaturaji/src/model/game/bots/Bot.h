//
// Created by robin on 19/12/2024.
//

#ifndef BOT_H
#define BOT_H
#include <utility>

#include "MoveStrategy.h"
#include "../state/identities/Player.h"


class Bot : public Player {
public:
    Bot(Color color, QString name, HomeBoardSide homeBoardSide, std::shared_ptr<MoveStrategy> strategy);
    QPoint getNextMove(Game& game, const QSet<ClassifiedMove>& moves);

private:
    std::shared_ptr<MoveStrategy> strategy;
};



#endif //BOT_H
