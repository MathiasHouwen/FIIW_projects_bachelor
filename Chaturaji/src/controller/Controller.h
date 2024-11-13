//
// Created by ebbew on 12-11-2024.
//

#ifndef CHATURAJI_CONTROLLER_H
#define CHATURAJI_CONTROLLER_H

#include <qobject.h>
#include <qobjectdefs.h>
#include "../model/Game.h"
#include "../view/BoardView.h"
#include "../view/DiceAndMovesView.h"

class Controller: public QObject{
Q_OBJECT

private:
    Game& model;
    BoardView* boardView;
    DiceAndMovesView* diceAndMovesView;
    QSet<QPoint> currentHighlights{};
    void start();
    void clearHighLights();
    void setSelectionHighlights();
    void setMoveHightlights();
    void setMoveAndDice();
public:
    Controller(Game &model, BoardView* boardView, DiceAndMovesView* diceAndMovesView);

private slots:
    void onCellClicked(QPoint cell);
    void onCellHoverChanged(QPoint cell, bool hover);
    void onSkipButtonClicked();
};


#endif //CHATURAJI_CONTROLLER_H
