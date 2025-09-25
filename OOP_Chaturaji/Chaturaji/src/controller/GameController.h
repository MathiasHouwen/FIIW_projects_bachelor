
//practicum 3:
// doel: game wrappen om controller clean te houden, en de state van de 2 stappen:
// pick up en place down managen (want dat is eigelijk iets typisch aan onze UI en hoort dus niet
// thuis in de Game class (waar het eerst wel was)
// - Ebbe: nieuwe class. Logica is gedeeltelijk afkomstig van de oude Controller class

#ifndef CHATURAJI_GAMECONTROLLER_H
#define CHATURAJI_GAMECONTROLLER_H


#include "../model/game/Game.h"

class GameController {
private:
    enum class StepState{READYTOPICK, READYTOPLACE};
    StepState state{StepState::READYTOPICK};
    Game game;
    std::optional<QPoint> selectedCell;
    MovesManager movesManager;
    BoardQuerier querier;
    void controllBot();
public:
    explicit GameController();
    QSet<ClassifiedMove> getMovesForHighlight();
    QSet<QPoint> getSelectablesForHighlight();
    void handleCellSelect(QPoint cell, PieceType pawnPromoteType = PieceType::PAWN);
    bool moveIsPawnPromote(QPoint cell);
    const std::optional<QPoint> &getSelectedCell() const;
    Game &getGame();
    void addBot(QString name, std::shared_ptr<MoveStrategy> strategy);
    void addPlayer(QString name);
    QString getCurrentPlayerName();
    void skip();
};


#endif //CHATURAJI_GAMECONTROLLER_H
