//
// Created by robin on 19/12/2024.
//

#include "Bot.h"

Bot::Bot(colour mColour, bool aggressive)
        : Player(mColour),
          aggressive(aggressive){
}

bool Bot::getAggressive() {
    return aggressive;
}
