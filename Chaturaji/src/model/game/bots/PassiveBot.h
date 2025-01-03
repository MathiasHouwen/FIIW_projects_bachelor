//
// Created by robin on 3/01/2025.
//

#ifndef PASSIVEBOT_H
#define PASSIVEBOT_H

#include "Bot.h"
#include "PassiveMoveStrategy.h"

class PassiveBot : public Bot {
public:
    explicit PassiveBot(colour mColour)
        : Bot(mColour, std::make_shared<PassiveMoveStrategy>()) {}
};

#endif //PASSIVEBOT_H
