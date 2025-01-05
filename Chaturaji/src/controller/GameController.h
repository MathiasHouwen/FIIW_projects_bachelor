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
    Game& game;
    std::optional<QPoint> selectedCell;
    MovesManager movesManager;
    BoardQuerier querier;
public:
    explicit GameController(Game& game);
    QSet<ClassifiedMove> getMovesForHighlight();
    QSet<QPoint> getSelectablesForHighlight();
    void handleCellSelect(QPoint cell, PieceType pawnPromoteType = PieceType::PAWN);
    bool moveIsPawnPromote(QPoint cell);
    StepState getState() const;
    const std::optional<QPoint> &getSelectedCell() const;

    Game &getGame() const;

};


#endif //CHATURAJI_GAMECONTROLLER_H
