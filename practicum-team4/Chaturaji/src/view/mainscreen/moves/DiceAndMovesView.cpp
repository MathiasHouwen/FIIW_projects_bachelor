//
// Created by ebbew on 13-11-2024.
//
//volledig van Ebbe


#include <QHBoxLayout>
#include <QPushButton>
#include "DiceAndMovesView.h"

void DiceAndMovesView::updateDiceNumbers(int die1, int die2) {
    diceViews[0]->updateNumber(die1);
    diceViews[1]->updateNumber(die2);
}

void DiceAndMovesView::updateDisableDie(int die, bool disabled) {
    diceViews[die]->updateDisabled(disabled);
}

DiceAndMovesView::DiceAndMovesView(QWidget *parent) : QWidget(parent) {
    // views
    diceViews[0] = new DieView(nullptr, 6);
    diceViews[1] = new DieView(nullptr, 6);
    moveLabel = new QLabel("MOVE: 1/2");
    auto skipButton = new QPushButton("SKIP");
    auto arrow = new QSvgWidget();

    //arrow init
    arrow->load(QString(ASSET_PATH) + "/arrow.svg");
    arrow->setFixedSize(50, 50);

    // layout init
    auto layout = new QHBoxLayout(parent);
    auto movesSection = new QVBoxLayout();
    piecePreviewsLayout = new QHBoxLayout();
    piecePreviewsLayout->setAlignment(Qt::AlignLeft);
    layout->setAlignment(Qt::AlignLeft);

    // layout add
    layout->addLayout(movesSection);
    movesSection->addWidget(moveLabel);
    movesSection->addWidget(skipButton);
    layout->addWidget(diceViews[0]);
    layout->addWidget(diceViews[1]);
    layout->addWidget(arrow);
    layout->addLayout(piecePreviewsLayout);

    // signals
    connect(skipButton, &QPushButton::clicked, this, &DiceAndMovesView::onSkipButtonClicked);
}

void DiceAndMovesView::updateMoveLabel(int move) {
    QString s;
    QTextStream ts(&s);
    ts << "Move " << move + 1 << " / 2";
    moveLabel->setText(s);
}

void DiceAndMovesView::updatePiecePreviews(QSet<PieceType> types) {
    for(auto pieceView : pieceViews){
        piecePreviewsLayout->removeWidget(pieceView);
        delete pieceView;
    }
    pieceViews.clear();
    for(auto type : types){
        auto pieceView = new PieceWidgit(nullptr, type);
        pieceView->setFixedSize(50, 50);
        pieceViews.insert(pieceView);
        piecePreviewsLayout->addWidget(pieceView);
    }
}

void DiceAndMovesView::onSkipButtonClicked() {
    emit skipButtonClicked();
}
