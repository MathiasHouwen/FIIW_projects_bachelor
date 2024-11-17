//
// Created by ebbew on 12-11-2024.
//

#include <QFileDialog>
#include "Controller.h"
#include "../model/FileIO.h"


Controller::Controller(Game &model, BoardView* boardView, DiceAndMovesView* diceAndMovesView, FileIOView* fileIoView, PlayersView* playersView)
        : QObject(nullptr), model(model), boardView(boardView),
        diceAndMovesView(diceAndMovesView), fileIoView(fileIoView), playersView(playersView){
    connect(boardView, &BoardView::cellClicked, this, &Controller::onCellClicked);
    connect(boardView, &BoardView::cellHoverChanged, this, &Controller::onCellHoverChanged);
    connect(diceAndMovesView, &DiceAndMovesView::skipButtonClicked, this, &Controller::onSkipButtonClicked);
    connect(fileIoView, &FileIOView::onLoad, this, &Controller::onLoad);
    connect(fileIoView, &FileIOView::onSave, this, &Controller::onSave);
}

void Controller::start() {
    io.loadBoard(&model, "../startingFile.txt");
    boardView->updateFullBoard(model.getBoard());
    clearHighLights();
    setSelectionHighlights();
    setMoveAndDice();
    initPlayersView();
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
        const Player& currentPlayer = model.getCurrentPlayer();
        bool succes = model.movePiece(cell);
        if(succes){
            const Player& newPlayer = model.getCurrentPlayer();
            boardView->updatePiece(selectedCell, nullptr);
            boardView->updatePiece(cell, model.getBoard().getCell(cell));
            clearHighLights();
            setSelectionHighlights();
            setMoveAndDice();
            playersView->updateScore(currentPlayer.getColour(), currentPlayer.getScore());
            playersView->updateSetBigAndToTop(newPlayer.getColour());
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
    playersView->updateSetBigAndToTop(model.getCurrentPlayer().getColour());
}

void Controller::onSave(){
    qDebug("Save button clicked!");
    QString filePath = QFileDialog::getSaveFileName(
            fileIoView,
            "Save File",
            "../Saves",
            "Text Files (*.txt)"
    );

    if (!filePath.isEmpty()) {
        if (!filePath.endsWith(".txt", Qt::CaseInsensitive)) {
            filePath += ".txt";
        }
        qDebug() << "Saving to file:" << filePath;

        io.save(&model, filePath);
    } else {
        qDebug() << ">:( Geen naam";
    }
}

void Controller::onLoad(){
    qDebug("Load button clicked!");
    QString filePath = QFileDialog::getOpenFileName(
            fileIoView,
            "Select a file to load",
            "../Saves",
            "Text Files (*.txt)"
    );

    if (!filePath.isEmpty()) {
        qDebug() << "FilePath:" << filePath;
        io.loadBoard(&model, filePath);
        boardView->updateFullBoard(model.getBoard());
        clearHighLights();
        setSelectionHighlights();
        initPlayersView();
    } else {
        qDebug() << ">:( Geen geldig filepath";
    }
}

void Controller::initPlayersView() {
    playersView->clear();
    for(Player::colour color : {Player::colour::RED, Player::colour::GREEN, Player::colour::BLUE, Player::colour::YELLOW}){
        Player p = model.getPlayerFromColour(color);
        playersView->addPlayerView(p);
        playersView->updateScore(p.getColour(), p.getScore());
    }
    playersView->updateSetBigAndToTop(model.getCurrentPlayer().getColour());
}
