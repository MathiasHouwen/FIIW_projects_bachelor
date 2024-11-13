#ifndef CHATURAJI_GAME_H
#define CHATURAJI_GAME_H


#include <qobject.h>
#include <qobjectdefs.h>

#include "Board.h"
#include "PatternMover.h"
#include "Player.h"
#include "Dice.h"

class Game: public QObject{
Q_OBJECT
signals:
    void somethingChanged();
public:
    enum class MoveState{READYTOSELECT, READYTOMOVE};
private:
    // model classes
    Board board;    // bord
    PatternMover mover; // logica voor piece patronen
    Dice dice;
    Player players[4] = {{Player::colour::RED}, {Player::colour::BLUE}, {Player::colour::YELLOW}, {Player::colour::GREEN}};

    // state
    QPoint* currentlySelectedCell;  // selectie, geen = null (1 move is eerst cell selecteren, dan volgende cell om te moven)
    MoveState moveState{MoveState::READYTOSELECT};
    int move{0};    // elke beurt heeft 2 moves (move = 0 / 1)
    int turn{0};    // player beurt (0-3)
    bool gameOver{false};

    void advance(); // zet game verder naar volgende move, of volgende turn als 2 moves geweest zijn

public:
    Game();
    //directe getters
    QPoint* getCurrentlySelectedCell() const;
    int getMove() const;
    Board& getBoard();
    bool isGameOver() const;
    MoveState getMoveState() const;

    Dice getDice();

    void skip();

    bool selectPiece(QPoint cell);  // selecteert een cell en returnt of die keuze geldig is
    bool movePiece(QPoint destinationCell); // selecteert de cell om de geselecteerde piece naar te verzetten en returnt of dit geldig is

    QSet<QPoint> getPossibleMoves(); // geeft de mogelijke bestemming-cells van de huidige geselecteerde piece (select=null->lege set)
    QSet<QPoint> getPossibleSelections();
    Player &getCurrentPlayer(); // player van de huidige turn
    Player &getPlayerFromColour(Player::colour colour); // zoek de player op basis van kleur
    const Player *getPlayers() const;

    void setPlayerName(const QString &name, Player::colour playerColour);

    void setPlayerScore(int score, Player::colour playerColour);
};


#endif //CHATURAJI_GAME_H
