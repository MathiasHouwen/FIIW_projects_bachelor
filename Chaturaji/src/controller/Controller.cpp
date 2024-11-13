//
// Created by ebbew on 12-11-2024.
//

#include "Controller.h"
#include "FileIO.h"

void Controller::onCellClicked(QPoint cell) {
    if(model.getMoveState() == Game::MoveState::READYTOSELECT){
        bool succes = model.selectPiece(cell);
        if(succes){
            clearHighLights();
            setMoveHightlights();
        }
    } else {// if(model.getMoveState() == Game::MoveState::READYTOMOVE) {
        QPoint selectedCell = *model.getCurrentlySelectedCell();
        bool succes = model.movePiece(cell);
        if(succes){
            boardView->updatePiece(selectedCell, nullptr);
            boardView->updatePiece(cell, model.getBoard().getCell(cell));
            clearHighLights();
            setSelectionHighlights();
        }
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
    clearHighLights();
    setSelectionHighlights();
}

void Controller::onCellHoverChanged(QPoint cell, bool hover) {
    if(hover && !currentHighlights.contains(cell)){
        boardView->updateHighlight(cell, SquareView::HighLight::HOVER);
    } else if(!currentHighlights.contains(cell)) {
        boardView->updateHighlight(cell, SquareView::HighLight::NONE);
    }
}

void Controller::clearHighLights() {
    for(QPoint cell : currentHighlights){
        boardView->updateHighlight(cell, SquareView::HighLight::NONE);
    }
    currentHighlights.clear();
}

void Controller::setSelectionHighlights() {
    auto selectables = model.getPossibleSelections();
    boardView->updateHighlights(selectables, SquareView::HighLight::SELECTSUGGEST);
    currentHighlights.unite(selectables);
}

void Controller::setMoveHightlights() {
    auto selectables = model.getPossibleMoves();
    for(QPoint cell : selectables){
        SquareView::HighLight highlight;
        if(model.getBoard().getCell(cell))
            highlight = SquareView::HighLight::ATTACKSUGGEST;
        else
            highlight = SquareView::HighLight::MOVESUGGEST;
        boardView->updateHighlight(cell, highlight);
        currentHighlights.insert(cell);
    }
    boardView->updateHighlight(*model.getCurrentlySelectedCell(), SquareView::HighLight::SELECTED);
    currentHighlights.insert(*model.getCurrentlySelectedCell());
}
