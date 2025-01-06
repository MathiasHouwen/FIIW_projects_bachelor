//
// Created by ebbew on 5-1-2025.
//

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
