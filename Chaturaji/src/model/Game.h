#ifndef CHATURAJI_GAME_H
#define CHATURAJI_GAME_H


#include "Board.h"

class Game {
private:
    Board board;
public:
    Game();
    const Board &getBoard() const;
};






#endif //CHATURAJI_GAME_H
