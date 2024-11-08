#ifndef CHATURAJI_GAMEVIEW_H
#define CHATURAJI_GAMEVIEW_H

#include "../model/Board.h"
#include "../model/Game.h"

class CLIView {
private:
    Game& model;
    static int asciiEscColorCode(Player::colour color); // vertaald color naar ascii escape color code
    static std::string getPieceSymbol(Piece piece); // geeft een woord voor het type van een piece
    static std::string asciiEscString(int color, int background, const std::string& str);   // gebruikt ascii escape characters om een string te kleuren
    std::string getCellString(QPoint cell) const;  // geeft de string met juist piece symbool en juiste kleur en highlight voor een cell
    void printBoard() const;
    void printDice() const;
    void printMove();
    void printTurn();
public:
    explicit CLIView(Game &game);
    void update(); // roept alle 4 print functies aan
};

#endif //CHATURAJI_GAMEVIEW_H
