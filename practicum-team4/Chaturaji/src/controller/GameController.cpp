// taakverdeling: zie h-file


#include "GameController.h"
#include "../model/game/bots/Bot.h"

QSet<ClassifiedMove> GameController::getMovesForHighlight() {
    if(state == StepState::READYTOPICK)
        return {};
    else{
        auto piece = game.getGameState().getBoard().getPieceAt(selectedCell.value());
        return movesManager.generateClassifiedMoves(piece.value(), selectedCell.value());
    }
}

GameController::GameController() :
    movesManager(game.getGameState().getBoard()),
    querier(game.getGameState().getBoard()){}

void GameController::handleCellSelect(QPoint cell, PieceType pawnPromoteType) {
    if(state == StepState::READYTOPICK){
        if(game.isCellAllowedToBePicked(cell)){
            qDebug() << "pick: " << cell;
            selectedCell = cell;
            state = StepState::READYTOPLACE;
        }
    } else {
        game.doMove(selectedCell.value(), cell, pawnPromoteType);
        qDebug() << "place: " << cell;
        selectedCell = std::nullopt;
        state = StepState::READYTOPICK;
    }
    if(game.getGameState().getCurrentPlayer()->isBot()){
        controllBot();
    }
}

bool GameController::moveIsPawnPromote(QPoint cell) {
    auto moves = getMovesForHighlight();
    for(auto move : moves){
        if(move.destination == cell){
            return move.specialMoveType == SpecialMoveType::PAWNPROMOTE;
        }
    }
    return false;
}

const std::optional<QPoint> &GameController::getSelectedCell() const {
    return selectedCell;
}

QSet<QPoint> GameController::getSelectablesForHighlight() {
    if(state == StepState::READYTOPLACE)
        return {};
    else{
        auto types = game.getGameState().getDice().getAllowedTypes();
        return querier.getPiecesWithTypesAndColor(types, game.getGameState().getCurrentTurn());
    }
}

Game &GameController::getGame() {
    return game;
}

void GameController::addBot(QString name, std::shared_ptr<MoveStrategy> strategy) {
    game.getGameState().addBot(name, strategy);
}

void GameController::addPlayer(QString name) {
    game.getGameState().addPlayer(name);
}

QString GameController::getCurrentPlayerName() {
    return game.getGameState().getCurrentPlayer()->getName();
}

void GameController::controllBot() {
    if(!game.getGameState().getCurrentPlayer()->isBot()) return;
    Bot* bot = static_cast<Bot *>(game.getGameState().getCurrentPlayer());
    if(state == StepState::READYTOPICK){
        auto selectables = getSelectablesForHighlight();
        auto selection = bot->getNextSelectedCell(game, selectables);
        handleCellSelect(selection);
        return;
    }
    auto moves = getMovesForHighlight();
    if(moves.isEmpty()){
        skip();
        return;
    }
    auto movePoint = bot->getNextMove(game, moves);
    handleCellSelect(movePoint);
}

void GameController::skip() {
    state = StepState::READYTOPICK;
    game.getGameState().advance();
    if(game.getGameState().getCurrentPlayer()->isBot()){
        controllBot();
    }
}


