//
// Created by ebbew on 12-11-2024.
//

#include "Controller.h"

void Controller::onCellClicked(QPoint cell) {
    std::cout <<  "clicked" << cell.x() << ", " << cell.y() << std::endl;
}

Controller::Controller(Game &model, BoardView &boardView)
    : QObject(nullptr), model(model), boardView(boardView) {

    connect(&boardView, &BoardView::cellClicked, this, &Controller::onCellClicked);
}
