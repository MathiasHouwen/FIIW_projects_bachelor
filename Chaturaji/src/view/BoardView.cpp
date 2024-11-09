//
// Created by ebbew on 8-11-2024.
//

#include <QPushButton>
#include <iostream>
#include <QPainter>
#include "BoardView.h"
#include "../model/Square.h"
#include "SquareView.h"

BoardView::BoardView(Game& model, QWidget *parent)
    : QWidget(parent), model(model) {
    rows = new QVBoxLayout(parent);
    rows->setSpacing(0);

    int size = Board::getSize();
    for(int i=0; i<size; i++){
        auto cols = new QHBoxLayout();
        cols->setSpacing(0);
        rows->addLayout(cols);
        for(int j=0; j<size; j++){
            auto s = new SquareView(nullptr, {i, j}, model);
            cols->addWidget(s);
        }
    }
}

BoardView::~BoardView() {

}

