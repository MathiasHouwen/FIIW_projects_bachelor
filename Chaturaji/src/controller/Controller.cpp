//
// Created by ebbew on 12-11-2024.
//
//nieuw sinds practicum 2 (controller class uit practicum 1 is 100% vervangen [verwijderd])

#include <QFileDialog>
#include <iostream>
#include "Controller.h"
#include "../model/io/FileIO.h"


Controller::Controller(GameController& gameController, BoardView* boardView, DiceAndMovesView* diceAndMovesView, FileIOView* fileIoView, PlayersView* playersView)
        : QObject(nullptr), gameController(gameController), boardView(boardView),
        diceAndMovesView(diceAndMovesView), fileIoView(fileIoView), playersView(playersView){
    // connect alle signals van views met de handlers in controller
    connect(boardView, &BoardView::cellClicked, this, &Controller::onCellClicked);
    connect(boardView, &BoardView::cellHoverChanged, this, &Controller::onCellHoverChanged);
    connect(diceAndMovesView, &DiceAndMovesView::skipButtonClicked, this, &Controller::onSkipButtonClicked);
    connect(fileIoView, &FileIOView::onLoad, this, &Controller::onLoad);
    connect(fileIoView, &FileIOView::onSave, this, &Controller::onSave);
}

void Controller::start() {
    io.load(gameController.getGame(), QString(SAVES_PATH) + "/startingFile.json");
    boardView->updateFullBoard(gameController.getGame().getGameState().getBoard());
    initPlayersView();
    update();
}
void Controller::onCellClicked(QPoint cell) {
    if(gameController.moveIsPawnPromote(cell)){
        // TODO pawn promote
        PieceType chosenType = PieceType::PAWN;
        gameController.handleCellSelect(cell, chosenType);
    } else {
        gameController.handleCellSelect(cell);
    }
    update();
}

//void Controller::startBot() {
//    std::cout << std::endl << "NEW MOVE:" << std::endl;
//    for(int i = 0 ; i < 2; i++) {
//        const QPoint cell = model.playBot();
//        onCellClicked(cell);
//        std::cout << "movePiece piece: " << cell.x() << "," << cell.y() << std::endl;
//        const QPoint destination = model.moveBotPiece();
//        if(destination == QPoint(NULL, NULL)) {
//            std::cout << "movePiece skipped: " << cell.x() << "," << cell.y() << std::endl;
//            model.skip();
//            updateMoveAndDiceView();
//            clearHighLights();
//            setSelectionHighlights();
//            playersView->updateSetBigAndToTop(model.getCurrentPlayer().getColor());
//        }
//        else {
//            std::cout << "moved: " << cell.x() << "," << cell.y() << " to: " << destination.x() << "," << destination.y() << std::endl;
//            onCellClicked(destination);
//        }
//    }
//}

// handle een enter of leave op een cell (gewoon een "cursor" highlight toepassen)
void Controller::onCellHoverChanged(QPoint cell, bool hover) {
    if(currentHighlights.contains(cell)) return; // behoud oude hightligts: hover highlight heeft lage prioriteit
    auto highlight = hover
            ? SquareView::HighLight::HOVER
            : SquareView::HighLight::NONE;
    boardView->updateHighlight(cell, highlight);
}

// cleart alle current highlights uit view (onthouden via private: currentHighlights chache)
void Controller::clearHighLights() {
    for(QPoint cell : currentHighlights)
        boardView->updateHighlight(cell, SquareView::HighLight::NONE);
    currentHighlights.clear();
}

// update de movePiece en dobbelstenen view
void Controller::updateMoveAndDiceView() {
    diceAndMovesView->updateMoveLabel(gameController.getGame().getGameState().getCurrentMove());
    diceAndMovesView->updateDiceNumbers(gameController.getGame().getGameState().getDice().asNumber(0), gameController.getGame().getGameState().getDice().asNumber(1));
    diceAndMovesView->updatePiecePreviews(gameController.getGame().getGameState().getDice().getAllowedTypes());
    diceAndMovesView->updateDisableDie(0, gameController.getGame().getGameState().getDice().isUsed(0));
    diceAndMovesView->updateDisableDie(1, gameController.getGame().getGameState().getDice().isUsed(1));
}

// handled een move skip (game::skip en update alles movePiece/turn gerelateerd)
void Controller::onSkipButtonClicked() {
    gameController.getGame().getGameState().advance();
    updateMoveAndDiceView();
    clearHighLights();
    updateHighlights();
    playersView->updateSetBigAndToTop(gameController.getGame().getGameState().getCurrentTurn());
}

//void Controller::endGame() {
//    std::cout << std::endl << "END GAME" << std::endl;
//    std::cout << "WINNER: " << gameController.getPlayer(gameController.getCurrentPlayer()).getName().toStdString() << std::endl;
//    _sleep(5000);
//    start();
//}

//handled de file save knop
//void Controller::onSave(){
//    qDebug("Save button clicked!");
//    QString filePath = QFileDialog::getSaveFileName(
//            fileIoView,
//            "Save File",
//            "../Saves",
//            "Text Files (*.txt)"
//    );
//
//    if (!filePath.isEmpty()) {
//        if (!filePath.endsWith(".txt", Qt::CaseInsensitive)) {
//            filePath += ".txt";
//        }
//        qDebug() << "Saving to file:" << filePath;
//
//        io.save(&model, filePath);
//    } else {
//        qDebug() << ">:( Geen naam";
//    }
//}

//handled de file load knop
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
        io.load(gameController.getGame(), filePath);
        boardView->updateFullBoard(gameController.getGame().getGameState().getBoard());
        update();
        initPlayersView();
    } else {
        qDebug() << ">:( Geen geldig filepath";
    }
}

void Controller::initPlayersView() {
    playersView->clear();
    for(Color color : {Color::RED, Color::GREEN, Color::BLUE, Color::YELLOW}){
        Player p = gameController.getGame().getGameState().getPlayerByColor(color);
        playersView->addPlayerView(p);
        playersView->updateScore(p.getColor(), p.getScore());
    }
    playersView->updateSetBigAndToTop(gameController.getGame().getGameState().getCurrentTurn());
}

void Controller::updateHighlights() {
    auto selectables = gameController.getSelectablesForHighlight();
    boardView->updateHighlights(selectables, SquareView::HighLight::SELECTSUGGEST);

    currentHighlights.unite(selectables);
    auto moves = gameController.getMovesForHighlight();
    for(auto move : moves){
        auto highlight = move.moveType == MoveType::NORMAL ? SquareView::HighLight::ATTACKSUGGEST
                                                           : SquareView::HighLight::MOVESUGGEST;
        boardView->updateHighlight(move.destination, highlight);
        currentHighlights.insert(move.destination);
    }

    auto selectedCell = gameController.getSelectedCell();
    if(selectedCell.has_value()){
        boardView->updateHighlight(selectedCell.value(), SquareView::HighLight::SELECTED);
    }
}

void Controller::update() {
    auto highlights = gameController.getMovesForHighlight();
    auto selectedCell = gameController.getSelectedCell();
    clearHighLights();
    updateHighlights();
    updateMoveAndDiceView();
    if(gameController.getGame().getGameState().isGameOver()){endGame();}
}
