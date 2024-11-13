//
// Created by ebbew on 8-11-2024.
//

#include <QPushButton>
#include <iostream>
#include <QPainter>
#include "BoardView.h"
#include "../model/Square.h"
#include "SquareView.h"

BoardView::BoardView(QWidget* parent) : QWidget(parent) {
    layout = new QGridLayout(this);
    layout->setSpacing(0);

    for(int x=0; x<Board::getSize(); x++){
    for(int y=0; y<Board::getSize(); y++){
        auto squareView = new SquareView(nullptr, {x, y});
        layout->addWidget(squareView, x, y);
    }}
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

BoardView::~BoardView() {

}

void BoardView::updateHighlight(QPoint cell, SquareView::HighLight highlight) {
    squareViews[cell.x()][cell.y()]->updateHighLight(highlight);
}

void BoardView::updateHighlights(const QList<QPoint>& cells, SquareView::HighLight highlight) {
    for(QPoint cell : cells){
        updateHighlight(cell, highlight);
    }
}

void BoardView::updatePiece(QPoint cell, Piece *piece) {
    squareViews[cell.x()][cell.y()]->updatePiece(piece);
}


