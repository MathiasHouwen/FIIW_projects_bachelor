#ifndef CHATURAJI_GAMEVIEW_H
#define CHATURAJI_GAMEVIEW_H

#include "../model/Board.h"
#include "../model/Game.h"

class GameView {
private:
    Game& model;
public:
    explicit GameView(Game &game);
    void printBoard() const;
    void printTypes(Piece::Type type) const;
};

#endif //CHATURAJI_GAMEVIEW_H
