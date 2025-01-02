//
// Created by robin on 2/01/2025.
//

#ifndef AGGRESSIVE_H
#define AGGRESSIVE_H

#include "Bot.h"

class Aggressive : public Bot {
public:
    explicit Aggressive(colour mColour)
        : Bot(mColour, true) {
    }
};



#endif //AGGRESSIVE_H
