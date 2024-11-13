//
// Created by ebbew on 13-11-2024.
//

#ifndef CHATURAJI_DICEANDMOVESVIEW_H
#define CHATURAJI_DICEANDMOVESVIEW_H


#include <QWidget>
#include <QLabel>

#include "DieView.h"
#include "PieceWidgit.h"

class DiceAndMovesView : public QWidget{
    Q_OBJECT
private:
public:
    DiceAndMovesView(QWidget *parent);
    void updateDiceNumbers(int die1, int die2);
    void updateDisableDie(int die);
    void updateEnableAllDice();

private:
    DieView* diceViews[2];
    QLabel* moveLabel;
    QSet<PieceWidgit*> pieceViews{};
};


#endif //CHATURAJI_DICEANDMOVESVIEW_H
