//
// Created by ebbew on 13-11-2024.
//
//volledig van Ebbe


#ifndef CHATURAJI_DICEANDMOVESVIEW_H
#define CHATURAJI_DICEANDMOVESVIEW_H


#include <QWidget>
#include <QLabel>

#include "DieView.h"
#include "../board/PieceWidgit.h"

class DiceAndMovesView : public QWidget{
    Q_OBJECT
public:
    DiceAndMovesView(QWidget *parent);
    void updateDiceNumbers(int die1, int die2);
    void updateDisableDie(int die, bool disabled);
    void updateMoveLabel(int move);
    void updatePiecePreviews(QSet<BadPieceClass::Type> types);

signals:
    void skipButtonClicked();

private slots:
    void onSkipButtonClicked();

private:
    DieView* diceViews[2];
    QLabel* moveLabel;
    QSet<PieceWidgit*> pieceViews{};
    QHBoxLayout* piecePreviewsLayout;
};


#endif //CHATURAJI_DICEANDMOVESVIEW_H
