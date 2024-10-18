#ifndef CHATURAJI_GAME_H
#define CHATURAJI_GAME_H


#include "Board.h"
#include "PatternMover.h"
#include "Player.h"

class Game {
private:
    Board board;    // bord
    PatternMover mover; // logica voor piece patronen
    QPoint* currentlySelectedCell;  // selectie, geen = null (1 move is eerst cell selecteren, dan volgende cell om te moven)
    QPair<Piece::Type, Piece::Type> dice;   // 2 piece types van de dobbelsteen

    int move{0};    // elke beurt heeft 2 moves (move = 0 / 1)
    int turn{0};    // player beurt (0-3)
    bool gameOver{false};
    Player players[4] = {{Player::colour::RED}, {Player::colour::BLUE}, {Player::colour::YELLOW}, {Player::colour::GREEN}};


public:
    Game();
    //directe getters
    QPoint* getCurrentlySelectedCell() const;
    const QPair<Piece::Type, Piece::Type> &getDice() const;
    int getMove() const;
    Board& getBoard();
    bool isGameOver() const;

    void doubleDobbel();    // geeft de dice nieuwe random waarden
    void namePlayer(const QString& name, int playerIndex);  // geeft een naam aan een player
    void advance(); // zet game verder naar volgende move, of volgende turn als 2 moves geweest zijn

    bool selectPiece(QPoint cell);  // selecteert een cell en returnt of die keuze geldig is
    bool movePiece(QPoint destinationCell); // selecteert de cell om de geselecteerde piece naar te verzetten en returnt of dit geldig is

    QSet<QPoint> getPossibleMoves(); // geeft de mogelijke bestemming-cells van de huidige geselecteerde piece (select=null->lege set)
    Player &getCurrentPlayer(); // player van de huidige turn
    Player &getPlayerFromColour(Player::colour colour); // zoek de player op basis van kleur
};


#endif //CHATURAJI_GAME_H
