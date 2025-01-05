//
// Created by robin on 19/12/2024.
//

#include "Bot.h"

#include <utility>

Bot::Bot(Color color, QString name, HomeBoardSide homeBoardSide, std::shared_ptr<MoveStrategy> strategy)
        : Player(color, std::move(name), homeBoardSide), strategy(std::move(strategy)) {
    bot = true;
}

QPoint Bot::getNextMove(Game& game, const QSet<ClassifiedMove>& moves) {
    return strategy->getNextMove(game, moves);
}
