//
// Created by ebbew on 12-11-2024.
//
//nieuw sinds practicum 2 (controller class uit practicum 1 is 100% vervangen [verwijderd])

#include <QFileDialog>
#include "Controller.h"
#include "../model/io/FileIO.h"


Controller::Controller(Game &model, BoardView* boardView, DiceAndMovesView* diceAndMovesView, FileIOView* fileIoView, PlayersView* playersView)
        : QObject(nullptr), model(model), boardView(boardView),
        diceAndMovesView(diceAndMovesView), fileIoView(fileIoView), playersView(playersView){
    // connect alle signals van views met de handlers in controller
    connect(boardView, &BoardView::cellClicked, this, &Controller::onCellClicked);
    connect(boardView, &BoardView::cellHoverChanged, this, &Controller::onCellHoverChanged);
    connect(diceAndMovesView, &DiceAndMovesView::skipButtonClicked, this, &Controller::onSkipButtonClicked);
    connect(fileIoView, &FileIOView::onLoad, this, &Controller::onLoad);
    connect(fileIoView, &FileIOView::onSave, this, &Controller::onSave);
}

// gebruikt om de controller apart te initialiseren.
// kan niet in constructor omdat sommige dingen zo vroeg nog niet geladen kunnen worden, zoals player namen uit het start scherm
// vandaar gebruikt om controller aan te maken bij het maken van main window, maar pas te initialiseren na window.show
void Controller::start() {
    io.loadBoard(&model, QString(SAVES_PATH) + "/startingFile.txt");
    boardView->updateFullBoard(model.getBoard());
    clearHighLights();
    setSelectionHighlights();
    setMoveAndDice();
    initPlayersView();
}

// handled wat er moet geberuen als er op een cell geklikt wordt:
// - is de game READY TO SELECT
//   -> vraag dan om die cell te selecteren (en update de view voor enkel die cell en zijn highlights)
// - is de game READY TO MOVE
//   -> vraaf dan om een movePiece te doen naar die cell (en update -idem)
//      is er een player affected in het resultaat van die movePiece: maak views grijs indien dood
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
        Game::MoveResult result = model.movePiece(cell);
        if(result.succes){

            if(model.vrihannauka(&selectedCell)){
                std::cout << "vrihannauka";
            }

//            // TODO: PAWN PROMATION
//            if(model.canPromote(&cell)){
//                // TODO: ASK FOR WICH PIECE TO PROMOTO IT TO
//            }
//
//
//            // TODO: sinhasana

            const Player& newPlayer = model.getCurrentPlayer();
            boardView->updatePiece(selectedCell, nullptr);
            boardView->updatePiece(cell, model.getBoard().getPieceAt(cell));
            clearHighLights();
            setSelectionHighlights();
            setMoveAndDice();
            playersView->updateScore(currentPlayer.getColour(), currentPlayer.getScore());
            playersView->updateSetBigAndToTop(newPlayer.getColour());
            if(result.affectedPlayer && !result.affectedPlayer->isAlive()) {
                playersView->updateSetGrey(result.affectedPlayer->getColour());
                for (auto piece: result.affectedPlayer->getAlivePieces()) {
                    boardView->updateSetPieceGrey(piece->getCell());
                }
            }
        }
    }
    if(model.getMoveState() == Game::MoveState::BOT) {
        startBot();
    }
    if(model.isGameOver()){endGame();}
}

void Controller::startBot() {
    std::cout << std::endl << "NEW MOVE:" << std::endl;
    for(int i = 0 ; i < 2; i++) {
        const QPoint cell = model.playBot();
        onCellClicked(cell);
        std::cout << "movePiece piece: " << cell.x() << "," << cell.y() << std::endl;
        const QPoint destination = model.moveBotPiece();
        if(destination == QPoint(NULL, NULL)) {
            std::cout << "movePiece skipped: " << cell.x() << "," << cell.y() << std::endl;
            model.skip();
            setMoveAndDice();
            clearHighLights();
            setSelectionHighlights();
            playersView->updateSetBigAndToTop(model.getCurrentPlayer().getColour());
        }
        else {
            std::cout << "moved: " << cell.x() << "," << cell.y() << " to: " << destination.x() << "," << destination.y() << std::endl;
            onCellClicked(destination);
        }
    }
}

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

// highlight cellen om te selecteren (possible selections)
void Controller::setSelectionHighlights() {
    auto selectables = model.getPossibleSelections();
    boardView->updateHighlights(selectables, SquareView::HighLight::SELECTSUGGEST);
    // onthoud de highlight in currentHighlights zodat clearhighlights deze cellen selectief kan updaten
    currentHighlights.unite(selectables);
}

// highlight cellen om naar te moven (possible moves)
void Controller::setMoveHightlights() {
    auto selectables = model.getPossibleMoves();
    for(QPoint cell : selectables){
        auto highlight = model.getBoard().getPieceAt(cell)
                ? SquareView::HighLight::ATTACKSUGGEST
                : SquareView::HighLight::MOVESUGGEST;
        boardView->updateHighlight(cell, highlight);
        // onthoud de highlight in currentHighlights zodat clearhighlights deze cellen selectief kan updaten
        currentHighlights.insert(cell);
    }
    boardView->updateHighlight(*model.getCurrentlySelectedCell(), SquareView::HighLight::SELECTED);
    // onthoud de highlight in currentHighlights zodat clearhighlights deze cellen selectief kan updaten
    currentHighlights.insert(*model.getCurrentlySelectedCell());
}

// update de movePiece en dobbelstenen view
void Controller::setMoveAndDice() {
    diceAndMovesView->updateMoveLabel(model.getMove());
    diceAndMovesView->updateDiceNumbers(model.getDice().getNumber(0), model.getDice().getNumber(1));
    diceAndMovesView->updatePiecePreviews(model.getDice().getAllowedTypes());
    diceAndMovesView->updateDisableDie(0, model.getDice().isUsed(0));
    diceAndMovesView->updateDisableDie(1, model.getDice().isUsed(1));
}

// handled een move skip (game::skip en update alles movePiece/turn gerelateerd)
void Controller::onSkipButtonClicked() {
    model.skip();
    setMoveAndDice();
    clearHighLights();
    setSelectionHighlights();
    playersView->updateSetBigAndToTop(model.getCurrentPlayer().getColour());
    if (model.getMoveState() == Game::MoveState::BOT) {
        startBot();
    }
    if(model.isGameOver()){endGame();}
}

void Controller::endGame() {
    std::cout << std::endl << "END GAME" << std::endl;
    std::cout << "WINNER: " << model.getCurrentPlayer().getName().toStdString() << std::endl;
    _sleep(5000);
    start();
}

//handled de file save knop
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
