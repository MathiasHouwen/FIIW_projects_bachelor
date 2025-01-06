//
// Created by ebbew on 8-11-2024.
//
//begin vooral door mathias gemaakt. door Ebbe goed werkend gemaakt


#include <QPushButton>
#include <iostream>
#include <QPainter>
#include "BoardView.h"
#include "SquareView.h"

BoardView::BoardView(QWidget* parent) : QWidget(parent) {
    layout = new QGridLayout(parent);
    layout->setSpacing(0);

    // maak square views
    // piece views staan hier apart van, odmat squareview permanent is en pieceview niet):
    int size = Board::dimension.getSize();
    for(int y=0; y<size; y++){
        for(int x=0; x<size; x++){
            auto squareView = new SquareView(nullptr, {x, y});
            connect(squareView, &SquareView::clicked, this, &BoardView::onSquareViewClicked);
            connect(squareView, &SquareView::hoverUpdated, this, &BoardView::onSquareHoverUpdated);
            layout->addWidget(squareView, y, x);
            squareViews[{x,y}] = squareView;
        }
    }
}


BoardView::~BoardView() {

}

void BoardView::updateHighlight(QPoint cell, SquareView::HighLight highlight) {
    squareViews[cell]->updateHighLight(highlight);
}

void BoardView::updateHighlights(const QSet<QPoint>& cells, SquareView::HighLight highlight) {
    for(QPoint cell : cells){
        updateHighlight(cell, highlight);
    }
}

void BoardView::updatePiece(QPoint cell, Piece piece) {
    squareViews[cell]->updatePiece(piece);
}


void BoardView::updateFullBoard(const Board &board) {
    int size = Board::dimension.getSize();

    for(int y=0; y<size; y++){
        for(int x=0; x<size; x++){
            auto piece = board.getPieceAt({x, y});
            if(piece.has_value())
                updatePiece({x,y}, piece.value());
            else
                removePiece({x,y});
        }
    }
}

// Signal relays:
void BoardView::onSquareViewClicked(QPoint cell) {emit cellClicked(cell);}
void BoardView::onSquareHoverUpdated(QPoint cell, bool hover) {emit cellHoverChanged(cell, hover);}

void BoardView::updateSetPieceGrey(QPoint cell) {
    squareViews[cell]->updateSetPieceGrey();
}

void BoardView::removePiece(QPoint cell) {
    squareViews[cell]->removePiece();
}




//BoardView::BoardView(Game& model, QWidget *parent)
//    : QWidget(parent), model(model) {
//    rows = new QVBoxLayout(parent);
//    rows->setSpacing(0);
//
//    int size = Board::getSize();
//    for(int i=0; i<size; i++){
//        auto cols = new QHBoxLayout();
//        cols->setSpacing(0);
//        rows->addLayout(cols);
//        for(int j=0; j<size; j++){
//            auto s = new SquareView(nullptr, {i, j}, model);
//            cols->addWidget(s);
//        }
//    }
//}

