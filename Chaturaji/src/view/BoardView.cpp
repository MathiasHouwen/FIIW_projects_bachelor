//
// Created by ebbew on 8-11-2024.
//

#include <QPushButton>
#include <iostream>
#include <QPainter>
#include "BoardView.h"
#include "../model/Square.h"
#include "SquareView.h"

BoardView::BoardView(QWidget *parent)
    : QWidget(parent) {
    rows = new QVBoxLayout(parent);
    rows->setSpacing(0);
    for(int i=0; i<8; i++){
        auto cols = new QHBoxLayout();
        cols->setSpacing(0);
        rows->addLayout(cols);
        for(int j=0; j<8; j++){
            auto s = new SquareView(nullptr, i, j);
            cols->addWidget(s);
        }
    }
}

BoardView::~BoardView() {

}

