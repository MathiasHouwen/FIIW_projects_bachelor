//
// Created by robin on 19/12/2024.
//

#include "Bot.h"

Bot::Bot(colour mColour, std::shared_ptr<MoveStrategy> strategy)
        : Player(mColour), strategy(std::move(strategy)) {}

QPoint Bot::getNextMove(Game& game, const QSet<QPoint>& moves) {
    return strategy->getNextMove(game, moves);
}
