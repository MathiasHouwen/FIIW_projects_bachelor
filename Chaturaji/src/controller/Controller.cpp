//
// Created by ebbew on 12-11-2024.
//

#include "Controller.h"
#include "FileIO.h"

void Controller::onCellClicked(QPoint cell) {
    if(model.getMoveState() == Game::MoveState::READYTOSELECT){
        model.selectPiece(cell);
        clearHighLights();
    } else {// if(model.getMoveState() == Game::MoveState::READYTOMOVE) {
        model.movePiece(cell);
        clearHighLights();
    }
}

Controller::Controller(Game &model, BoardView* boardView)
    : QObject(nullptr), model(model), boardView(boardView) {
    connect(boardView, &BoardView::cellClicked, this, &Controller::onCellClicked);
    connect(boardView, &BoardView::cellHoverChanged, this, &Controller::onCellHoverChanged);
    start();
}

void Controller::start() {
    FileIO io;
    io.loadBoard(&model, "../startingFile.txt");
    boardView->updateFullBoard(model.getBoard());
}

void Controller::onCellHoverChanged(QPoint cell, bool hover) {
    if(hover){
        boardView->updateHighlight(cell, SquareView::HighLight::HOVER);
    } else {
        boardView->updateHighlight(cell, SquareView::HighLight::NONE);
    }
}

void Controller::clearHighLights() {
    for(QPoint cell : currentHighlights){
        boardView->updateHighlight(cell, SquareView::HighLight::NONE);
    }
    currentHighlights.clear();
}

void Controller::setHighLights() {

}
