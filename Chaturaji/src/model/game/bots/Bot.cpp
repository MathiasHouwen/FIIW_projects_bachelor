//
// Created by robin on 19/12/2024.
//

#include "Bot.h"

Bot::Bot(Color color, std::shared_ptr<MoveStrategy> strategy)
        : Player(color, "bot"), strategy(std::move(strategy)) {}

QPoint Bot::getNextMove(Game& game, const QSet<QPoint>& moves) {
    return strategy->getNextMove(game, moves);
}
