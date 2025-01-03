//
// Created by robin on 3/01/2025.
//

#ifndef AGGRESSIVEBOT_H
#define AGGRESSIVEBOT_H



#include "Bot.h"
#include "AggressiveMoveStrategy.h"

class AggressiveBot : public Bot {
public:
    explicit AggressiveBot(colour mColour)
        : Bot(mColour, std::make_shared<AggressiveMoveStrategy>()) {}
};



#endif //AGGRESSIVEBOT_H
