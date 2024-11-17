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
#include "../view/FileIOView.h"
#include "../view/PlayersView.h"

class Controller: public QObject{
Q_OBJECT

private:
    Game& model;
    BoardView* boardView;
    DiceAndMovesView* diceAndMovesView;
    FileIOView* fileIoView;
    PlayersView* playersView;
    FileIO io;
    QSet<QPoint> currentHighlights{};
    void clearHighLights();
    void setSelectionHighlights();
    void setMoveHightlights();
    void setMoveAndDice();
    void initPlayersView();
public:
    Controller(Game &model, BoardView* boardView, DiceAndMovesView* diceAndMovesView, FileIOView* fileIoView, PlayersView* playersView);
    void start();

private slots:
    void onCellClicked(QPoint cell);
    void onCellHoverChanged(QPoint cell, bool hover);
    void onSkipButtonClicked();
    void onLoad();
    void onSave();
};


#endif //CHATURAJI_CONTROLLER_H
