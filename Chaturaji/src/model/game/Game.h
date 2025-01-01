#ifndef CHATURAJI_GAME_H
#define CHATURAJI_GAME_H


#include "board/Board.h"
#include "../logic/PatternMover.h"
#include "Player.h"
#include "Dice.h"
#include "Bot.h"

// practicum 2: resultaat van move vervangen van bool tot MoveResult
// + state machine karakter van game duidelijker gemaakt in de public interface, door MoveState enum
// voor de rest minimale veranderingen
// door iedereen van de groep

class Game{
public:
    enum class MoveState{READYTOSELECT, READYTOMOVE, BOT};
    struct MoveResult{
        bool succes{false};
        Player* affectedPlayer{nullptr};
        Piece* affectedPiece{nullptr};
    };
private:
    const static int numberOfPlayer = 4;

    // model classes
    Board board;    // bord
    PatternMover mover; // logica voor piece patronen
    Dice dice;
    std::vector<std::shared_ptr<Player>> players = {
        std::make_shared<Player>(Player::colour::RED),
        std::make_shared<Player>(Player::colour::BLUE),
        std::make_shared<Player>(Player::colour::YELLOW),
        std::make_shared<Player>(Player::colour::GREEN)
    };

    // state
    QPoint* currentlySelectedCell;  // selectie, geen = null (1 move is eerst cell selecteren, dan volgende cell om te moven)
    MoveState moveState{MoveState::READYTOSELECT};
    int move{0};    // elke beurt heeft 2 moves (move = 0 / 1)
    int turn{0};    // player beurt (0-3)
    bool gameOver{false};

    void advance(); // zet game verder naar volgende move, of volgende turn als 2 moves geweest zijn
    QPoint getNextMove(QSet<QPoint> moves);

    void mergeArmies(Player *fromPlayer, Player *toPlayer);
    bool isSquareFilledWithBoats(QPoint topLeft);
    void captureBoats(QPoint topLeft, Player &safe);

public:
    Game();
    //directe getters
    QPoint* getCurrentlySelectedCell() const;
    int getMove() const;
    Board& getBoard();
    bool isGameOver() const;
    MoveState getMoveState() const;

    void makeBot(Player::colour color, bool agressive);
    QPoint playBot();
    QPoint moveBotPiece();

    Dice getDice();

    void skip();

    // game is een state machine, en wisselt telkens tussen select en move
    bool selectPiece(QPoint cell);  // selecteert een cell en returnt of die keuze geldig is
    MoveResult movePiece(QPoint destinationCell); // selecteert de cell om de geselecteerde piece naar te verzetten en returnt of dit geldig is

    QSet<QPoint> getPossibleMoves(); // geeft de mogelijke bestemming-cells van de huidige geselecteerde piece (select=null->lege set)
    QSet<QPoint> getPossibleSelections();
    Player &getCurrentPlayer(); // player van de huidige turn
    Player &getPlayerFromColour(Player::colour colour); // zoek de player op basis van kleur
    std::vector<std::shared_ptr<Player>> getPlayers() const;

    void setPlayerName(const QString &name, Player::colour playerColour);
    void setPlayerScore(int score, Player::colour playerColour);
    static const int getNumberOfPlayer();

    bool canPromote(QPoint *selectedCell);
    bool promote(QPoint *selectedCell);

    bool sinhasana(QPoint *selectedCell);
    bool vrihannauka(QPoint *selectedCell);

};


#endif //CHATURAJI_GAME_H
