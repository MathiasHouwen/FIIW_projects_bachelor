#ifndef CHATURAJI_GAMEVIEW_H
#define CHATURAJI_GAMEVIEW_H

#include "../model/Board.h"
#include "../model/Game.h"

class GameView {
private:
    Game& model;
    static int asciiEscColorCode(Player::colour color);
    static std::string getPieceSymbol(Piece piece);
    static std::string asciiEscString(int color, int background, const std::string& str);
    std::string getCellString(QPoint cell) const;
public:
    explicit GameView(Game &game);
    void printBoard() const;
    void printTypes(Piece::Type type) const;
};

#endif //CHATURAJI_GAMEVIEW_H
