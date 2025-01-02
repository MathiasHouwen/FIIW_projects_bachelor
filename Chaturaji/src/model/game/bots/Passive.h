//
// Created by robin on 2/01/2025.
//

#ifndef PASSIVE_H
#define PASSIVE_H

#include "Bot.h"


class Passive : public Bot {
public:
    explicit Passive(colour mColour)
        : Bot(mColour, false) {
    }
};



#endif //PASSIVE_H
