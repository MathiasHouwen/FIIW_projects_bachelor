//
// Created by ebbew on 13-11-2024.
//

#include <QHBoxLayout>
#include <QPushButton>
#include "DiceAndMovesView.h"

void DiceAndMovesView::updateDiceNumbers(int die1, int die2) {

}

void DiceAndMovesView::updateDisableDie(int die) {

}

void DiceAndMovesView::updateEnableAllDice() {

}

DiceAndMovesView::DiceAndMovesView(QWidget *parent) : QWidget(parent) {
    diceViews[0] = new DieView(nullptr, 6);
    diceViews[1] = new DieView(nullptr, 6);

    auto layout = new QHBoxLayout(parent);
    layout->setAlignment(Qt::AlignLeft);
    auto movesSection = new QVBoxLayout();
    layout->addLayout(movesSection);

    auto skipButton = new QPushButton("SKIP");
    moveLabel = new QLabel("MOVE: 1/2");

    movesSection->addWidget(moveLabel);
    movesSection->addWidget(skipButton);

    layout->addWidget(diceViews[0]);
    layout->addWidget(diceViews[1]);

    auto arrow = new QSvgWidget();
    arrow->load(QString(ASSET_PATH) + "/arrow.svg");
    arrow->setFixedSize(50, 50);
    layout->addWidget(arrow);

    auto piece1 = new PieceWidgit(nullptr, Piece::Type::KING);
    piece1->setFixedSize(50, 50);
    auto piece2 = new PieceWidgit(nullptr, Piece::Type::PAWN);
    piece2->setFixedSize(50, 50);
    auto piece3 = new PieceWidgit(nullptr, Piece::Type::KNIGHT);
    piece3->setFixedSize(50, 50);

    layout->addWidget(piece1);
    layout->addWidget(piece2);
    layout->addWidget(piece3);

}
