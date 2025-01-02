//
// Created by robin on 19/12/2024.
//

#ifndef BOT_H
#define BOT_H
#include "../Player.h"


class Bot : public Player{
public:
    Bot(colour mColour, bool aggressive);
    bool getAggressive();

private:
    bool aggressive;
};



#endif //BOT_H
