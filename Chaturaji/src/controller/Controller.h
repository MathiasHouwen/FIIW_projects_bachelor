//
// Created by ebbew on 12-11-2024.
//

//nieuw sinds practicum 2 (controller class uit practicum 1 is 100% vervangen [verwijderd])
//gemaakt door ebbe. onload en onsave slots gemaakt door mathias
// doel van controller: logica specifiek aan selectieve view updates los koppelen van model

#ifndef CHATURAJI_CONTROLLER_H
#define CHATURAJI_CONTROLLER_H

#include <qobject.h>
#include <qobjectdefs.h>
#include "../view/mainscreen/board/BoardView.h"
#include "../view/mainscreen/moves/DiceAndMovesView.h"
#include "../view/mainscreen/toolbar/FileIOView.h"
#include "../view/mainscreen/player/PlayersView.h"
#include "GameController.h"

class Controller: public QObject{
Q_OBJECT

private:
    GameController& gameController;

    BoardView* boardView;
    DiceAndMovesView* diceAndMovesView;
    FileIOView* fileIoView;
    PlayersView* playersView;

    FileIO io;
    QSet<QPoint> currentHighlights{};

    int numberOfBotMoves = 2;
    void clearHighLights();
    void updateHighlights();
    void updateMoveAndDiceView();
    void initPlayersView();
    void endGame();
    void update();
    PieceType openPawnPromoteDialog();
public:
    Controller(GameController& gameController, BoardView* boardView, DiceAndMovesView* diceAndMovesView, FileIOView* fileIoView, PlayersView* playersView);
    void start();
    void startBot();

private slots:
    void onCellClicked(QPoint cell);
    void onCellHoverChanged(QPoint cell, bool hover);
    void onSkipButtonClicked();
    void onLoad();
    void onSave();
};


#endif //CHATURAJI_CONTROLLER_H
