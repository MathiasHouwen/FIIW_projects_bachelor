//
// Created by ebbew on 12-11-2024.
//

#include "Controller.h"
#include "FileIO.h"


Controller::Controller(Game &model, BoardView* boardView, DiceAndMovesView* diceAndMovesView)
        : QObject(nullptr), model(model), boardView(boardView), diceAndMovesView(diceAndMovesView) {
    connect(boardView, &BoardView::cellClicked, this, &Controller::onCellClicked);
    connect(boardView, &BoardView::cellHoverChanged, this, &Controller::onCellHoverChanged);
    connect(diceAndMovesView, &DiceAndMovesView::skipButtonClicked, this, &Controller::onSkipButtonClicked);
    start();
}

void Controller::start() {
    FileIO io;
    io.loadBoard(&model, "../startingFile.txt");
    boardView->updateFullBoard(model.getBoard());
    clearHighLights();
    setSelectionHighlights();
    setMoveAndDice();
}

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
            setMoveAndDice();
        }
    }
}

void Controller::onCellHoverChanged(QPoint cell, bool hover) {
    if(currentHighlights.contains(cell)) return; // behoud oude hightligts: hover highlight heeft lage prioriteit
    auto highlight = hover
            ? SquareView::HighLight::HOVER
            : SquareView::HighLight::NONE;
    boardView->updateHighlight(cell, highlight);
}

void Controller::clearHighLights() {
    for(QPoint cell : currentHighlights)
        boardView->updateHighlight(cell, SquareView::HighLight::NONE);
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
        auto highlight = model.getBoard().getCell(cell)
                ? SquareView::HighLight::ATTACKSUGGEST
                : SquareView::HighLight::MOVESUGGEST;
        boardView->updateHighlight(cell, highlight);
        currentHighlights.insert(cell);
    }
    boardView->updateHighlight(*model.getCurrentlySelectedCell(), SquareView::HighLight::SELECTED);
    currentHighlights.insert(*model.getCurrentlySelectedCell());
}

void Controller::setMoveAndDice() {
    diceAndMovesView->updateMoveLabel(model.getMove());
    diceAndMovesView->updateDiceNumbers(model.getDice().getNumber(0), model.getDice().getNumber(1));
    diceAndMovesView->updatePiecePreviews(model.getDice().getAllowedTypes());
    diceAndMovesView->updateDisableDie(0, model.getDice().isUsed(0));
    diceAndMovesView->updateDisableDie(1, model.getDice().isUsed(1));
}

void Controller::onSkipButtonClicked() {
    model.skip();
    setMoveAndDice();
    clearHighLights();
    setSelectionHighlights();
}
